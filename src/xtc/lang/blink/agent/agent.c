#include <jni.h>
#include <jvmti.h>
#include <assert.h>

#include "agent_main.h"
#include "state.h"
#include "options.h"
#include "agent.h"
#include "util.h"
#include "state.h"
#include "agent_class.h"

/* agent java methods. */
struct java_static_method {
    jmethodID methodid;
    const char *name;
    const char *desc;
};

JNIEXPORT void JNICALL bda_j2c(JNIEnv *env, jclass clz);
JNIEXPORT jint JNICALL bda_get_process_id(JNIEnv *env, jclass clz);

/* agent classes*/
static jclass agent_class = NULL;
static jclass agent_variable_class = NULL;

/* a list of Blink agent's special native methods. */
static const JNINativeMethod agent_native_methods[] =
{
  { "getProcessID", "()I", bda_get_process_id },
  { "j2c", "()V", bda_j2c },
};

static struct java_static_method agent_java_method_init = 
{NULL, "init", "()V"};
static struct java_static_method agent_java_method_jbp = 
{NULL, "jbp", "()V"};
static struct java_static_method agent_java_method_dummy_java =
{NULL, "dummyJava", "()I"};

static struct java_static_method bda_meth_cv_set_boolean = 
{NULL, "set", "(Z)I"};
static struct java_static_method bda_meth_cv_set_int = 
{NULL, "set", "(I)I"};
static struct java_static_method bda_meth_cv_set_double = 
{NULL, "set", "(D)I"};
static struct java_static_method bda_meth_cv_set_object = 
{NULL, "set", "(Ljava/lang/Object;)I"};

static struct java_static_method agent_var_set_j2c_boolean = 
{NULL, "getAsBoolean", "(I)Z"};
static struct java_static_method agent_var_set_j2c_int = 
{NULL, "getAsInt", "(I)I"};
static struct java_static_method agent_var_set_j2c_double =
{NULL, "getAsDouble", "(I)D"};
static struct java_static_method agent_var_set_j2c_object = 
{NULL, "getAsObject", "(I)Ljava/lang/Object;"};

/* Java and c transition breakpoint points */
int bda_j2c_call_breakpoint = 0;
int bda_j2c_return_breakpoint = 0;
int bda_c2j_call_breakpoint = 0;
int bda_c2j_return_breakpoint = 0;
int bda_transition_count = 0;

/* get jnienv pointer value for the current thread. */
static JNIEnv *bda_ensure_jnienv()
{
  JNIEnv *env;
  jint res;

  assert(bda_jvm != NULL);
  res = (*bda_jvm)->AttachCurrentThread(bda_jvm, (void **)&env, NULL);
  assert(res >= 0 && env != NULL);

  return env;
}

static void bda_cache_static_java_method_id(
    JNIEnv *env, jclass clazz, 
    int is_static,
    struct java_static_method *meth)
{
    const char *mname = meth->name;
    const char *mdesc = meth->desc;
    jmethodID mid;
    if (is_static) { 
        mid = bda_orig_jni_funcs->GetStaticMethodID(env, clazz, mname, mdesc);
    } else {
        mid = bda_orig_jni_funcs->GetMethodID(env, clazz, mname, mdesc);
    }
    assert(mid);
    meth->methodid = mid;
}

static jclass load_global_agent_class(
    JNIEnv *env, const char *cname, const jbyte *buf, jsize len)
{
  jclass jclass_ref_local, jclass_ref_global;

  jclass_ref_local = bda_orig_jni_funcs->DefineClass(env, cname, NULL, buf, len);
  assert(jclass_ref_local != NULL);
  jclass_ref_global = bda_orig_jni_funcs->NewGlobalRef(env, jclass_ref_local);
  assert(jclass_ref_global != NULL);
  return jclass_ref_global;
}

void bda_agent_init(JNIEnv *env)
{
    jint jni_result;

    /* obtain a agent class reference. */
    agent_class = load_global_agent_class(
        env, AGENT_CLASS_NAME, class_agent, sizeof(class_agent));
    agent_variable_class = load_global_agent_class(
        env, AGENT_VARIABLE_CLASS_NAME, class_agent_variable,
        sizeof(class_agent_variable));

    /* obtain agent Java method identifiers. */
    bda_cache_static_java_method_id(env, agent_class, 1, &agent_java_method_init);
    bda_cache_static_java_method_id(env, agent_class, 1, &agent_java_method_jbp);
    bda_cache_static_java_method_id(env, agent_class, 1, &agent_java_method_dummy_java);
    bda_cache_static_java_method_id(env, agent_variable_class, 1, &bda_meth_cv_set_boolean);
    bda_cache_static_java_method_id(env, agent_variable_class, 1, &bda_meth_cv_set_int);
    bda_cache_static_java_method_id(env, agent_variable_class, 1, &bda_meth_cv_set_double);
    bda_cache_static_java_method_id(env, agent_variable_class, 1, &bda_meth_cv_set_object);
    bda_cache_static_java_method_id(env, agent_variable_class, 1, &agent_var_set_j2c_boolean);
    bda_cache_static_java_method_id(env, agent_variable_class, 1, &agent_var_set_j2c_int);
    bda_cache_static_java_method_id(env, agent_variable_class, 1, &agent_var_set_j2c_double);
    bda_cache_static_java_method_id(env, agent_variable_class, 1, &agent_var_set_j2c_object);

    /* register agent's native methods. */
    jni_result = bda_orig_jni_funcs->RegisterNatives(env, agent_class,
                                         agent_native_methods,
                                         sizeof(agent_native_methods)/sizeof(JNINativeMethod));
    assert(!jni_result);
    
    /* initialize java part of the agent. */
    bda_orig_jni_funcs->CallStaticVoidMethod(env, agent_class, agent_java_method_init.methodid);
    if (bda_orig_jni_funcs->ExceptionCheck(env)) {
        bda_orig_jni_funcs->ExceptionDescribe(env);
        assert(0);
    }
}

/* 
 * The entry procedure for the c2j method. This is for the native code
 * to call the "Agent.c2j() method. 
 */
int bda_c2j()
{
    JNIEnv *env;
    assert(agent_java_method_jbp.methodid != NULL);
    env = bda_ensure_jnienv();
    bda_orig_jni_funcs->CallStaticVoidMethod(env, agent_class, agent_java_method_jbp.methodid);
    return 1;
}

JNIEXPORT void JNICALL bda_j2c(JNIEnv *env, jclass clz)
{
    void *c2j_return_addr, *c2j_prev_fp;
    void *saved_return_addr, *saved_prev_fp;
    /*This is executed by JDWP agent internally, but we want to skip
    the JDWP agent's stack. Therefore, bda_j2c has special call frame
    stitching unlike the other j2c proxies. */
    struct bda_state_info*  s = bda_get_state_info(env);
    struct bda_jni_function_frame const * c2j = s->head_c2j;
    while(c2j != NULL && bda_is_in_jdwp_region(c2j->return_addr)) {
        c2j = c2j->prev;
    }
    if (c2j != NULL) {
        c2j_return_addr = c2j->return_addr;
        c2j_prev_fp =  c2j->caller_fp;
    } else {
        c2j_return_addr = NULL;
        c2j_prev_fp = NULL;
    }
    
    /* stitch this frame. */
    GET_RETURN_ADDRESS(saved_return_addr);
    GET_PREVIOUS_FRAME_POINTER(saved_prev_fp);
    SET_RETURN_ADDRESS(c2j_return_addr);
    SET_PREVIOUS_FRAME_POINTER(c2j_prev_fp);

    /* trigger break point. */
    bda_cbp(J2C_DEBUGGER, s, NULL);

    /* unstitch this frame.*/
    SET_RETURN_ADDRESS(saved_return_addr);
    SET_PREVIOUS_FRAME_POINTER(saved_prev_fp);
}

JNIEXPORT jint JNICALL bda_get_process_id(JNIEnv *env, jclass clz)
{
  jint pid = GET_CURRENT_PROCESS_ID();
  return pid;
}


extern int bda_dummy_java() 
{
  JNIEnv *env;
  int result;
  env = bda_ensure_jnienv();
  result = bda_orig_jni_funcs->CallStaticIntMethod(env, agent_class, 
                               agent_java_method_dummy_java.methodid);
  return result;
}

/* Dummy function for the portable internal Blink break point. */
void bda_cbp(
    breakpoint_type bptype, 
    struct bda_state_info *state, 
    struct bda_location *target)
{
}

int bda_is_agent_native_method(void *address) 
{
  int i;
  for(i=0; i < sizeof(agent_native_methods)/sizeof(JNINativeMethod);i++) {
      if (agent_native_methods[i].fnPtr == address ) {
          return 1;
      }
  }
  return 0;
}

/* FIXME: perhaps just too bad implementation now. */
const char *bda_cstr(jstring jstr) 
{
    static char buf[256];
    int i;

    JNIEnv *env = bda_ensure_jnienv();
    int strsize = bda_orig_jni_funcs->GetStringUTFLength(env, jstr);
    const char *str = bda_orig_jni_funcs->GetStringUTFChars(env, jstr, NULL);

    if (strsize > 128) {
        strsize = 128;
    }
    for(i=0; i < strsize;i++) {
        buf[i] = str[i];
    }
    buf[i] = '\0';

    bda_orig_jni_funcs->ReleaseStringUTFChars(env, jstr, str);

    return buf;
}

int bda_cv_set_jboolean(jboolean exprValue)
{
    JNIEnv *env = bda_ensure_jnienv();
    return (*env)->CallStaticIntMethod(
        env, agent_variable_class, 
        bda_meth_cv_set_boolean.methodid, 
        exprValue);
}

int bda_cv_set_jint(jint exprValue)
{
    JNIEnv *env = bda_ensure_jnienv();
    return (*env)->CallStaticIntMethod(
        env, agent_variable_class, 
        bda_meth_cv_set_int.methodid, 
        exprValue);
}

int bda_cv_set_jdouble(jdouble exprValue)
{
    JNIEnv *env = bda_ensure_jnienv();
    return (*env)->CallStaticIntMethod(
        env, agent_variable_class, 
        bda_meth_cv_set_double.methodid,
        exprValue);
}

int bda_cv_set_jobject(jobject exprValue)
{
    JNIEnv *env = bda_ensure_jnienv();
    return (*env)->CallStaticIntMethod(
        env, agent_variable_class, 
        bda_meth_cv_set_object.methodid,
        exprValue);
}

jboolean bda_cv_get_jboolean(int vjid)
{
    JNIEnv *env = bda_ensure_jnienv();
    return (*env)->CallStaticBooleanMethod(
        env, agent_variable_class,
        agent_var_set_j2c_boolean.methodid,
        vjid);
}

jint bda_cv_get_jint(int vjid)
{
    JNIEnv *env = bda_ensure_jnienv();
    return (*env)->CallStaticIntMethod(
        env, agent_variable_class,
        agent_var_set_j2c_int.methodid,
        vjid);
}

jdouble bda_cv_get_jdouble(int vjid)
{
    JNIEnv *env = bda_ensure_jnienv();
    return (*env)->CallStaticDoubleMethod(
        env, agent_variable_class,
        agent_var_set_j2c_double.methodid,
        vjid);
}

jobject bda_cv_get_jobject(int vjid)
{
    JNIEnv *env = bda_ensure_jnienv();
    jobject lref, gref;

    lref = (*env)->CallStaticObjectMethod(
        env, 
        agent_variable_class,
        agent_var_set_j2c_object.methodid,
        vjid);
    gref = (*env)->NewGlobalRef(env, lref);
    //TODO: Free global references at the end of expression evaluation.
    return gref;
}
