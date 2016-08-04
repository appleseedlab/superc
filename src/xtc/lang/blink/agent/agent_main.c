#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <jni.h>
#include <jvmti.h>

#include "state.h"
#include "options.h"
#include "util.h"
#include "jnicheck.h"

/* function declarations */
static void JNICALL agent_vm_init(jvmtiEnv *jvmti, JNIEnv *env, jthread thread);
static void JNICALL agent_vm_bind(jvmtiEnv *jvmti, JNIEnv *env,
                                  jthread thread, jmethodID method,
                                  void *address, void **new_address_ptr);
static void JNICALL agent_vm_death(jvmtiEnv *jvmti, JNIEnv *env);
static void JNICALL agent_vm_thread_start(jvmtiEnv *jvmti, JNIEnv *env, jthread t);
static void JNICALL agent_vm_thread_end(jvmtiEnv *jvmti, JNIEnv *env, jthread t);

/* variable definitions */
JavaVM *bda_jvm = NULL; /* The Java virtual machine */
jvmtiEnv *bda_jvmti = NULL; /* This JVMTI handle from JVM. */
jniNativeInterface *bda_orig_jni_funcs = NULL; /* JNI function table */

/* jdwp region. */
void *bda_jdwp_region_begin = NULL;
void *bda_jdwp_region_end = NULL;

int bda_is_in_jdwp_region(void *address)
{
    return ((bda_jdwp_region_begin != NULL) 
            && (bda_jdwp_region_end != NULL) 
            && (address >= bda_jdwp_region_begin) 
            && (address < bda_jdwp_region_end));
}


/* function definitions. */
JNIEXPORT jint JNICALL Agent_OnLoad(JavaVM *vm, char *options, void *reserved)
{
  jvmtiError err;
  jvmtiCapabilities capa;
  jvmtiEventCallbacks callbacks;
  jvmtiEnv *jvmti;
  int rc;

  assert(bda_jvm == NULL && vm != NULL);
  bda_jvm = vm;

  /* Parse incoming options. */
  agent_parse_options(options);

  /* Ensure JVMTI agent capabilities. */
  rc = (*vm)->GetEnv(vm, (void**)&jvmti, JVMTI_VERSION_1);
  assert(rc == JNI_OK);
  err = (*jvmti)->GetCapabilities(jvmti, &capa);
  assert(err == JVMTI_ERROR_NONE);
  if (agent_options.interpose) {
      if (!capa.can_generate_native_method_bind_events) {
          capa.can_generate_native_method_bind_events = 1;
          err = (*jvmti)->AddCapabilities(jvmti, &capa);
          assert(err == JVMTI_ERROR_NONE);
      }
      if (!capa.can_get_bytecodes) {
          capa.can_get_bytecodes = 1;
          err = (*jvmti)->AddCapabilities(jvmti, &capa);
          assert(err == JVMTI_ERROR_NONE);
      }
      if (!capa.can_get_line_numbers) {
          capa.can_get_line_numbers = 1;
          err = (*jvmti)->AddCapabilities(jvmti, &capa);
          assert(err == JVMTI_ERROR_NONE);
      }
  }

  bda_j2c_proxy_init();

  /* Initialize the JVMTI event call backs. */
  memset(&callbacks, 0, sizeof(callbacks));
  callbacks.VMInit = &agent_vm_init;
  callbacks.VMDeath = &agent_vm_death;
  callbacks.ThreadStart = &agent_vm_thread_start;
  callbacks.ThreadEnd = &agent_vm_thread_end;
  if (agent_options.interpose) {
      callbacks.NativeMethodBind = &agent_vm_bind;
  }

  err = (*jvmti)->SetEventCallbacks(jvmti, &callbacks, sizeof(callbacks));
  assert(err == JVMTI_ERROR_NONE);

  err = (*jvmti)->SetEventNotificationMode(jvmti, JVMTI_ENABLE, 
                                           JVMTI_EVENT_VM_DEATH, NULL);
  assert(err == JVMTI_ERROR_NONE);

  if (agent_options.interpose) {
      err = (*jvmti)->SetEventNotificationMode(jvmti, JVMTI_ENABLE,
                                               JVMTI_EVENT_NATIVE_METHOD_BIND, NULL);
      assert(err == JVMTI_ERROR_NONE);
  }

  err = (*jvmti)->SetEventNotificationMode(jvmti, JVMTI_ENABLE, 
                                           JVMTI_EVENT_VM_INIT, NULL);
  assert(err == JVMTI_ERROR_NONE);

  err = (*jvmti)->SetEventNotificationMode(jvmti, JVMTI_ENABLE, 
                                           JVMTI_EVENT_THREAD_START, NULL);
  assert(err == JVMTI_ERROR_NONE);

  err = (*jvmti)->SetEventNotificationMode(jvmti, JVMTI_ENABLE, 
                                           JVMTI_EVENT_THREAD_END, NULL);
  assert(err == JVMTI_ERROR_NONE);

  bda_jvmti = jvmti;

  return 0;
}

JNIEXPORT void JNICALL Agent_OnUnload(JavaVM *vm)
{
}

static void JNICALL agent_vm_init(jvmtiEnv *jvmti, JNIEnv *env, jthread thread)
{
  jvmtiError err;

  /* set c2j jni proxies. */
  err = (*jvmti)->GetJNIFunctionTable(jvmti, &bda_orig_jni_funcs);
  assert(err == JVMTI_ERROR_NONE);
  if (agent_options.interpose) {
      bda_c2j_proxy_install(jvmti);
  }

  bda_agent_init(env);

  if (agent_options.jinn) {
      bda_jnicheck_init(env);
  }

  /* enable deferred native proxies during pridomial phase. */
  if (agent_options.interpose) {
      bda_j2c_proxy_deferred_methods_reregister(jvmti, env);
  }
}


static void JNICALL agent_vm_death(jvmtiEnv *jvmti, JNIEnv *env)
{
  if (agent_options.jinn) {
      bda_jnicheck_exit(env);
  }

  bda_jvmti = NULL;
}

static void JNICALL agent_vm_bind(jvmtiEnv *jvmti, JNIEnv *env,
                                jthread thread, jmethodID method,
                                void *address, void **new_address_ptr)
{
  jvmtiPhase phase;
  jvmtiError err;
  err = (*jvmti)->GetPhase(jvmti, &phase);
  assert(err == JVMTI_ERROR_NONE);
  if (!bda_is_agent_native_method(address)) {
    switch(phase) {
    case JVMTI_PHASE_ONLOAD:
    case JVMTI_PHASE_PRIMORDIAL:
        bda_j2c_proxy_add_deferred(method, address);
      break;
    case JVMTI_PHASE_START:
    case JVMTI_PHASE_LIVE: {
        bda_j2c_proxy_add(jvmti, env, method, address, new_address_ptr);
        break;
    }
    default:
      assert(0); /* not reachable. */
      break;
    }
  }
}

static void JNICALL agent_vm_thread_start(jvmtiEnv *jvmti, JNIEnv *env, jthread t)
{
  jvmtiError err;
  jvmtiPhase phase;
  jvmtiThreadInfo tinfo;
  struct bda_state_info *s;
  char *tname = NULL;

  /* check phase*/
  err = (*jvmti)->GetPhase(jvmti, &phase);
  assert(err == JVMTI_ERROR_NONE);
  if (phase != JVMTI_PHASE_LIVE) {
    return;
  }

  s = bda_state_allocate(env);

  err = (*jvmti)->GetThreadInfo(jvmti, t, &tinfo);
  assert(err == JVMTI_ERROR_NONE);  
  tname=malloc(strlen(tinfo.name)+1);
  strcpy(tname, tinfo.name);
  s->thread_name = tname;

  err = (*jvmti)->Deallocate(jvmti, (unsigned char *)tinfo.name);
  assert(err == JVMTI_ERROR_NONE);  

  err = (*jvmti)->SetThreadLocalStorage(jvmti, NULL, (void*)s);
  assert(err == JVMTI_ERROR_NONE);

  bda_tls_state = s;
}

static void JNICALL agent_vm_thread_end(jvmtiEnv *jvmti, JNIEnv *env, jthread t)
{
  jvmtiError err;
  struct bda_state_info *s = NULL;

  err = (*jvmti)->GetThreadLocalStorage(jvmti, NULL, (void**)&s);
  assert(err == JVMTI_ERROR_NONE);
  if (s == NULL) {
      return; /* This happens in some JVMs. */
  }
  err = (*jvmti)->SetThreadLocalStorage(jvmti, NULL, NULL);
  assert(err == JVMTI_ERROR_NONE);

  if (agent_options.stats) {
      printf("$STAT$:%12d %12d %-20s\n", s->j2c_counts, s->c2j_counts, s->thread_name);
  }
  bda_state_free(s);

  bda_tls_state = NULL;
}
