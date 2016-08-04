#include <assert.h>
#include <string.h>
#include <jni.h>
#include <jvmti.h>
#include <classfile_constants.h>
#include <stdarg.h>
#include <stdlib.h>

#include "agent_main.h"
#include "state.h"
#include "agent.h"
#include "jnicheck.h"
#include "util.h"
#include "options.h"
#include "agent_class.h"

#define HTABLE_BUCKET_SIZE (16)

struct hentry {
    void *key;
    void *value;
    struct hentry *next;
};

struct htable {
    struct hentry *buckets[HTABLE_BUCKET_SIZE];
    int count;
};

struct bda_local_frame
{
  int sentinel;
  int capacity;
  int count;
  jobject *list;
  struct bda_local_frame *next;
};

struct bda_method_info {
  jmethodID mid;
  jint modifier;
  short is_static;
  const char **argumentTypes;
  const char *returnType;
  const char *cdesc;
  const char *mname;
  const char *mdesc;
};

struct bda_field_info {
  jclass decl_clazz_gref;
  jfieldID fid;
  jint modifier;
  int mutable_final;
  const char *cdesc;
  const char *fname;
  const char *fdesc; /* "java/lang/String" or "Ljava/lang/String;" */
};

struct bda_monitor_state {
  jobject object;
  int count;
  struct bda_monitor_state *next;
};

static int bda_local_ref_live(struct bda_state_info *s, jobject o);

static jclass bda_clazz_string = NULL;
static jclass bda_clazz_class = NULL;
static jclass bda_clazz_method = NULL;
static jclass bda_clazz_booleanArray = NULL;
static jclass bda_clazz_byteArray = NULL;
static jclass bda_clazz_charArray = NULL;
static jclass bda_clazz_shortArray = NULL;
static jclass bda_clazz_intArray = NULL;
static jclass bda_clazz_longArray = NULL;
static jclass bda_clazz_floatArray = NULL;
static jclass bda_clazz_doubleArray = NULL;
static jclass bda_clazz_constructor = NULL;
static jclass agent_jni_assertion_failure_class = NULL;

jclass bda_clazz_classloader = NULL;
jclass bda_clazz_throwable = NULL;
jclass bda_clazz_field = NULL;
jclass bda_clazz_nio_buffer = NULL;

static jmethodID bda_assert_failure_string = NULL;
static jmethodID jni_assert_failure_throwable = NULL;

MUTEX_DECL(bda_global_resources_lock)

static struct htable *bda_jmethods;
static struct htable *bda_jfields;
static struct htable *bda_global_ref_table = NULL;
static struct htable *bda_weak_global_ref_table = NULL;
static struct htable *bda_resource_table = NULL;
static struct bda_monitor_state *bda_monitor_state_head = NULL;

struct htable *htable_create()
{
    struct htable *t;

    t = malloc(sizeof (struct htable));
    memset(t, 0, sizeof (struct htable));

    return t;
}

void htable_destroy(struct htable *t)
{
    struct hentry *e, *next;
    int i;

    for(i = 0; i < HTABLE_BUCKET_SIZE;i++) {
        e = t->buckets[i];        
        while (e != NULL) {
            next = e->next;
            free(e);
            e = next;
        }
    }
    free(t);
}

int htable_hash(void *key)
{
    return (unsigned)key % (unsigned)HTABLE_BUCKET_SIZE;
}

void htable_put(struct htable *t, void *key, void *value)
{
    struct hentry *hnew;
    int h;

    hnew = (struct hentry *)malloc(sizeof(struct hentry));
    hnew->key = key;
    hnew->value = value;
    h=htable_hash(key);
    hnew->next = t->buckets[h];
    t->buckets[h] = hnew;
    t->count++;
}

void *htable_get(struct htable *t, void *key)
{
    struct hentry *e;
    int h;

    h=htable_hash(key);
    e = t->buckets[h];
    while (e != NULL) {
        if (e->key == key) {
            return e->value;
        }
        e = e->next;
    }
    return NULL;
}

void htable_remove(struct htable *t, void *key)
{
    struct hentry *e, *prev;
    int h;
    h=htable_hash(key);
    
    prev = NULL;
    e = t->buckets[h];
    while (e != NULL) {
        if (e->key == key) {
            if (prev == NULL) {
                t->buckets[h] = e->next;
            } else {
                prev->next = e->next;
            }
            free(e);
            t->count--;
            return;
        }
        prev = e;
        e = e->next;
    }
}

int htable_count(struct htable *t)
{
    return t->count;
}


static jclass bda_ensure_global_clazz(JNIEnv *env, const char *cdesc)
{
  jclass clazz;
  clazz = bda_orig_jni_funcs->FindClass(env, cdesc);
  assert(clazz != NULL);
  clazz = bda_orig_jni_funcs->NewGlobalRef(env, clazz);
  assert(clazz != NULL);
  return clazz;
}

static jmethodID bda_ensure_static_methodid(
    JNIEnv *env, jclass clazz,
    const char *mname, const char *mdesc)
{
    jmethodID mid = bda_orig_jni_funcs->GetStaticMethodID(env, clazz, mname, mdesc);
    assert(mid != NULL);
    return mid;
}

void bda_jnicheck_init(JNIEnv *env)
{
  bda_resource_table = htable_create();
  bda_global_ref_table = htable_create();
  bda_weak_global_ref_table = htable_create();
  bda_jmethods=htable_create();
  bda_jfields=htable_create();
  MUTEX_INIT(bda_global_resources_lock);

  bda_clazz_string = bda_ensure_global_clazz(env, "java/lang/String");
  bda_clazz_class = bda_ensure_global_clazz(env, "java/lang/Class");
  bda_clazz_classloader = bda_ensure_global_clazz(env, "java/lang/ClassLoader");
  bda_clazz_throwable = bda_ensure_global_clazz(env, "java/lang/Throwable");
  bda_clazz_booleanArray = bda_ensure_global_clazz(env, "[Z");
  bda_clazz_byteArray = bda_ensure_global_clazz(env, "[B");
  bda_clazz_charArray = bda_ensure_global_clazz(env, "[C");
  bda_clazz_shortArray = bda_ensure_global_clazz(env, "[S");
  bda_clazz_intArray = bda_ensure_global_clazz(env, "[I");
  bda_clazz_longArray = bda_ensure_global_clazz(env, "[J");
  bda_clazz_floatArray = bda_ensure_global_clazz(env, "[F");
  bda_clazz_doubleArray = bda_ensure_global_clazz(env, "[D");
  bda_clazz_field = bda_ensure_global_clazz(env, "java/lang/reflect/Field");
  bda_clazz_method = bda_ensure_global_clazz(env, "java/lang/reflect/Method");
  bda_clazz_constructor = bda_ensure_global_clazz(env, "java/lang/reflect/Constructor");
  bda_clazz_nio_buffer = bda_ensure_global_clazz(env, "java/nio/Buffer");

  agent_jni_assertion_failure_class = bda_orig_jni_funcs->DefineClass(
      env, AGENT_JNI_ASSERTION_FAILURE_CLASS_NAME,
      NULL,
      class_agent_jni_assertion_failure,
      sizeof(class_agent_jni_assertion_failure));
  assert(agent_jni_assertion_failure_class != NULL);
  agent_jni_assertion_failure_class = bda_orig_jni_funcs->NewGlobalRef(
      env, agent_jni_assertion_failure_class);
  assert(agent_jni_assertion_failure_class != NULL);
  bda_assert_failure_string = bda_orig_jni_funcs->GetStaticMethodID(
      env, agent_jni_assertion_failure_class, 
      "assertFail", "(Ljava/lang/String;)V");
  jni_assert_failure_throwable = bda_ensure_static_methodid(
      env, agent_jni_assertion_failure_class, 
      "assertFail", "(Ljava/lang/String;Ljava/lang/Throwable;)V");

}

void jinn_assertion_fail(
    struct bda_state_info *state, 
    jthrowable pending_exception, 
    const char* fmt, ...) 
{
  va_list ap;
  char msgbuf[1024];

  va_start(ap, fmt);
  vsnprintf(msgbuf, sizeof(msgbuf), fmt, ap);
  va_end(ap);

  assert(!bda_orig_jni_funcs->ExceptionCheck(state->env));
  state->msgbuf=msgbuf;
  bda_cbp(JNI_WARNING, state, NULL);
  if (agent_options.jinn) {
      if (agent_options.failstop) {
          jstring jmsg;

          jmsg = bda_orig_jni_funcs->NewStringUTF(state->env, msgbuf);
          assert(jmsg != NULL);
          if (pending_exception) {
              bda_orig_jni_funcs->CallStaticVoidMethod(
                  state->env, agent_jni_assertion_failure_class,
                  jni_assert_failure_throwable,
                  jmsg, pending_exception);
          } else {
              bda_orig_jni_funcs->CallStaticVoidMethod(
                  state->env, agent_jni_assertion_failure_class,
                  bda_assert_failure_string, jmsg);
          }
          bda_orig_jni_funcs->DeleteLocalRef(state->env, jmsg);
      } else {
          printf("%s\n", msgbuf);
      }
  }
}

void bda_jnicheck_exit(JNIEnv *env)
{
    bda_check_resource_leak(env);
    bda_check_monitor_leak(env);
    bda_check_global_ref_leak(env);
    bda_check_weak_global_ref_leak(env);
}

static struct bda_method_info 
*bda_method_info_lookup(jmethodID mid)
{
    struct bda_method_info *minfo = NULL;

    MUTEX_LOCK(bda_global_resources_lock);
    minfo = (struct bda_method_info*)htable_get(bda_jmethods, mid);
    MUTEX_UNLOCK(bda_global_resources_lock);

    return minfo;
}


void bda_jmethodid_append(
    jmethodID mid, short is_static, jclass clazz, 
    const char *mname, const char *mdesc)
{
  struct bda_method_info *minfo = NULL;

  minfo = bda_method_info_lookup(mid);
  if (minfo == NULL) {
    jint modifier;
    jvmtiError err;
    char *cdesc;

    err = (*bda_jvmti)->GetMethodModifiers(bda_jvmti, mid, &modifier);
    assert (err == JVMTI_ERROR_NONE);
    if (is_static) {
      assert( (modifier & JVM_ACC_STATIC) == JVM_ACC_STATIC);
    } else {
      assert( (modifier & JVM_ACC_STATIC) != JVM_ACC_STATIC);
    }
    err = (*bda_jvmti)->GetClassSignature(bda_jvmti, clazz, &cdesc, NULL);
    assert (err == JVMTI_ERROR_NONE);

    minfo = (struct bda_method_info *)malloc(sizeof *minfo);
    memset(minfo, 0, sizeof *minfo);
    minfo->is_static = is_static;
    minfo->mid = mid;
    minfo->modifier = modifier;
    minfo->mname = malloc(strlen(mname) + 1);
    strcpy((char*)minfo->mname, mname);
    minfo->mdesc = malloc(strlen(mdesc) + 1);
    strcpy((char*)minfo->mdesc, mdesc);
    minfo->cdesc = malloc(strlen(cdesc) + 1);
    strcpy((char*)minfo->cdesc, cdesc);
    bda_parse_method_descriptor(mdesc, &minfo->argumentTypes, &minfo->returnType);

    err = (*bda_jvmti)->Deallocate(bda_jvmti, (unsigned char*)cdesc);
    assert (err == JVMTI_ERROR_NONE);    

    MUTEX_LOCK(bda_global_resources_lock);
    htable_put(bda_jmethods, mid, minfo);
    MUTEX_UNLOCK(bda_global_resources_lock);
  }
}

static struct bda_field_info 
*bda_jfieldID_lookup(struct bda_state_info *s, 
                     jclass decl_clazz, jfieldID fid, 
                     jboolean is_static)
{
    struct hentry *e;
    struct bda_field_info *found = NULL;
    int i;

    MUTEX_LOCK(bda_global_resources_lock);
    for(i=0; i < HTABLE_BUCKET_SIZE;i++) {
        for(e=bda_jfields->buckets[i];e != NULL;e=e->next) {
            struct bda_field_info *finfo;

            finfo = (struct bda_field_info *)e->key;
            if ((finfo->fid == fid) && 
                bda_orig_jni_funcs->IsSameObject(s->env, decl_clazz, finfo->decl_clazz_gref)) {
                found = finfo;
                break;
            }
        }
        if (found != NULL)
            break;
    }
    MUTEX_UNLOCK(bda_global_resources_lock);

    return found;
}

static char *bda_str_dup(const char *s)
{
  char *new_s = malloc(strlen(s)+1);
  assert(new_s != NULL);
  strcpy(new_s, s);
  return new_s;
}

static char *bda_str_dup_fdesc_to_cdesc(const char *s)
{
  if (s[0] == 'L') {
    int size = strlen(s)-1;
    char *new_s = malloc(size);
    strncpy(new_s, s+1, size - 1);
    new_s[size-1] = '\0';
    return new_s;
  } else {
    return bda_str_dup(s);
  }
}

void bda_jfieldid_append(
    struct bda_state_info *s, jfieldID fid, jclass clazz, 
    short is_static, const char* name, const char *desc)
{
  struct bda_field_info *finfo;
  jvmtiError err;
  jclass decl_clazz;

  err = (*bda_jvmti)->GetFieldDeclaringClass(bda_jvmti, clazz, fid, &decl_clazz);
  assert(err == JVMTI_ERROR_NONE);

  /* Search for field information entry. */
  finfo = bda_jfieldID_lookup(s, decl_clazz, fid, is_static);
  if (finfo == NULL) {
      jint modifier;
      char *csig;

      finfo = malloc(sizeof *finfo);
      memset(finfo, 0, sizeof *finfo);

      err = (*bda_jvmti)->GetFieldModifiers(bda_jvmti, decl_clazz, fid, &modifier);
      assert (err == JVMTI_ERROR_NONE);
      err = (*bda_jvmti)->GetClassSignature(bda_jvmti, decl_clazz, &csig, NULL);
      assert (err == JVMTI_ERROR_NONE);

      finfo->decl_clazz_gref = bda_orig_jni_funcs->NewGlobalRef(s->env, decl_clazz);
      assert(finfo->decl_clazz_gref != NULL);
      finfo->cdesc = bda_str_dup_fdesc_to_cdesc(csig);
      finfo->fname = bda_str_dup(name);
      finfo->fdesc = bda_str_dup(desc);
      finfo->fid = fid;
      finfo->modifier = modifier;
      finfo->mutable_final = !strcmp(csig, "Ljava/lang/System;") 
          && (!strcmp(name, "out")||!strcmp(name, "in")||!strcmp(name, "err"));

      err = (*bda_jvmti)->Deallocate(bda_jvmti, (unsigned char*)csig);
      assert (err == JVMTI_ERROR_NONE);

      MUTEX_LOCK(bda_global_resources_lock);
      htable_put(bda_jfields, finfo, finfo);
      MUTEX_UNLOCK(bda_global_resources_lock);
  }
  bda_orig_jni_funcs->DeleteLocalRef(s->env, decl_clazz);
}


static int bda_check_live(struct bda_state_info *s, jobject o)
{
  int is_live = 0;
  assert(o != NULL);  

  if (s->mode == SYS_NATIVE) {
      return 1;
  }

  if (bda_local_ref_live(s, o)) {
    return 1;
  }

  MUTEX_LOCK(bda_global_resources_lock);
  is_live = (htable_get(bda_global_ref_table, (void*)o) != NULL)
      || (htable_get(bda_weak_global_ref_table, (void*)o) != NULL);
  MUTEX_UNLOCK(bda_global_resources_lock);

  return is_live;
}

void bda_thread_context_init(struct bda_state_info *s)
{
    s->critical = 0;
    s->open_criticals = htable_create();
    s->local_frame_top = NULL;
}

void bda_thread_context_destroy(struct bda_state_info *s)
{
    assert(s->critical == 0);
    htable_destroy(s->open_criticals);
    s->open_criticals = NULL;
}

void bda_local_ref_enter(struct bda_state_info *s, int capacity, int sentinel)
{
  struct bda_local_frame * new_frame;
  jobject * ref_list;

  /* Allocate memory. */
  assert(capacity >= -1);
  new_frame = (struct bda_local_frame*)malloc(sizeof(struct bda_local_frame));
  assert(new_frame != NULL);
  if (capacity > 0) {
    ref_list =  (jobject *)calloc(capacity, sizeof(jobject));
    memset(ref_list, 0, sizeof(jobject) * capacity);
    assert(ref_list != NULL);
  } else {
    ref_list = NULL;
  }

  /* Create and add a frame. */
  new_frame->sentinel = sentinel;
  new_frame->capacity = capacity;
  new_frame->count = 0;
  new_frame->list = ref_list;
  new_frame->next = s->local_frame_top;
  s->local_frame_top = new_frame;  
}

void bda_local_ref_leave(struct bda_state_info *s)
{
  struct bda_local_frame * top_frame;
  struct bda_local_frame * next_top_frame;
  jobject * top_ref_list;

  top_frame = s->local_frame_top;
  assert(top_frame != NULL);  
  top_ref_list = top_frame->list;
  next_top_frame = top_frame->next;

  if (top_frame->capacity > 0) {
    assert(top_ref_list != NULL);
    free(top_ref_list);
  } else {
    assert(top_ref_list == NULL);
  }
  free(top_frame);

  s->local_frame_top = next_top_frame;
}

static int bda_local_ref_live(struct bda_state_info *s, jobject o)
{
  struct bda_local_frame * frame;
  int i;

  for (frame = s->local_frame_top; frame != NULL; frame = frame->next){
    for(i = frame->count -1; i >= 0;i--) {
      if (frame->list[i] == o) {
        return 1;
      }
    }
  }
  return 0;
}

void bda_local_ref_add(struct bda_state_info *s, jobject o)
{
  struct bda_local_frame * top_frame;

  top_frame = s->local_frame_top;
  assert((o != NULL) &&(top_frame->count < top_frame->capacity));
  if (top_frame->count < top_frame->capacity) {
    top_frame->list[top_frame->count++] = o;
  }
}


void bda_local_ref_delete(struct bda_state_info *s, jobject o)
{
  struct bda_local_frame * frame;
  int i, ref_index;

  assert(o != NULL);  
  ref_index = -1;
  for(frame = s->local_frame_top;(frame != NULL);frame = frame->next){
    for(i = frame->count - 1; i >= 0;i--) {
      if (frame->list[i] == o) {
        ref_index = i;
        goto DONE;
      }
    }
  }
DONE:
  if ((frame != NULL) && (ref_index >= 0)) {
      for(i = ref_index; i < (frame->count - 1); i++) {
          frame->list[i] = frame->list[i + 1];
      }
      frame->count--;
  } else {
      assert(s->mode != USR_NATIVE);
  }
  return;
}

void bda_global_ref_add(jobject o, int weak)
{
  MUTEX_LOCK(bda_global_resources_lock);
  if (weak) {
    htable_put(bda_weak_global_ref_table, (void *)o, (void *)o);
  } else {
    htable_put(bda_global_ref_table, (void *)o, (void *)o);
  }
  MUTEX_UNLOCK(bda_global_resources_lock);
}

void bda_global_ref_delete(jobject o, int weak)
{
  MUTEX_LOCK(bda_global_resources_lock);
  if (weak) {
    htable_remove(bda_weak_global_ref_table, (void*)o);
  } else {
    htable_remove(bda_global_ref_table, (void*)o);
  }
  MUTEX_UNLOCK(bda_global_resources_lock);
}

int bda_check_global_ref_leak(JNIEnv *env)
{
    int rst = 0;
    MUTEX_LOCK(bda_global_resources_lock);
    if (htable_count(bda_global_ref_table) > 0) {
        int i;
        struct hentry *e;

        printf("The following global references are alive.\n");
        for(i=0; i < HTABLE_BUCKET_SIZE;i++)
            for(e=bda_global_ref_table->buckets[i];e != NULL;e=e->next) {
                jobject o = (jobject)e->key;
                printf("%10p\n", o);
            }
        rst = 0;
    } else {
        rst = 1;
    }
    MUTEX_UNLOCK(bda_global_resources_lock);
    return rst;
}

int bda_check_weak_global_ref_leak(JNIEnv *env)
{
    if (htable_count(bda_weak_global_ref_table) > 0) {
        int i;
        struct hentry *e;
        printf("The following weak global references are alive.\n");
        for(i=0; i < HTABLE_BUCKET_SIZE;i++)
            for(e=bda_weak_global_ref_table->buckets[i];e != NULL;e=e->next) {
                jobject o = (jobject)e->key;
                printf("%10p\n", o);
            }
        return 0;
    } else {
        return 1;
    }
}

int bda_check_env_match(struct bda_state_info *s, JNIEnv *env, const char *fname)
{
  if (env != s->env){
    jinn_assertion_fail(
        s, NULL, "The JNI environment %p does not match %p for the current thread in %s.",
        env, s->env, fname);
    return 0;
  }
  return 1;
}

int bda_check_no_exeception(struct bda_state_info *s, const char *fname)
{
  if (bda_orig_jni_funcs->ExceptionCheck(s->env) == JNI_TRUE){
    jthrowable t = bda_orig_jni_funcs->ExceptionOccurred(s->env);
    bda_orig_jni_funcs->ExceptionDescribe (s->env);
    bda_orig_jni_funcs->ExceptionClear(s->env);
    assert(t != NULL);
    jinn_assertion_fail(
        s, t, "An exception is pending in %s.", fname);
    bda_orig_jni_funcs->DeleteLocalRef(s->env, t);
    return 0;
  }

  return 1;
}

int bda_check_non_null(struct bda_state_info *s, const void* o, int index, const char *fname)
{
  if ((o == NULL) || (o == ((void*)0xFFFFFFFF))) {
      jinn_assertion_fail(
          s, NULL, "The argument %d can not be null in %s.", index + 1, fname);
      return 0;
  }
  return 1;
}

static int  bda_check_field_common(struct bda_state_info *s, 
                                   struct bda_field_info *finfo, 
                                   jfieldID fid,
                                   jclass oclass, jboolean is_static, 
                                   const char *func_name) 
{
  if (finfo == NULL) {
      jinn_assertion_fail(
          s, NULL, "The fieldID %p is not valid in %s.", fid, func_name);
    return 0;
  }

  if (is_static == JNI_TRUE) {
    if ((finfo->modifier & JVM_ACC_STATIC) != JVM_ACC_STATIC) {
        jinn_assertion_fail(
            s, NULL, "The fieldID %p is not a static field in %s.", fid, func_name);
      return 0;
    }
  } else {
    assert(is_static == JNI_FALSE);
    if ((finfo->modifier & JVM_ACC_STATIC) == JVM_ACC_STATIC) {
      jinn_assertion_fail(
        s, NULL, "The fieldID %p is not an instance field in %s.", fid, func_name);
      return 0;
    }
  }
  return 1;
}

static const char *bda_jmethod_primitive_name(char c)
{
  switch(c) {
  case 'Z': return "jboolean";
  case 'B': return "jbyte";
  case 'C': return "jchar";
  case 'I': return "jint";
  case 'S': return "jshort";
  case 'J': return "jlong";
  case 'F': return "jfloat";
  case 'D': return "jdouble";
  default:
    assert(0);
    return "";
  }
}

static int bda_check_field_type_getter(
    struct bda_state_info *s, 
    struct bda_field_info* finfo, 
    jclass oclass,
    char vt, const char *func_name)
{
  const char *fdesc;
  
  fdesc = finfo->fdesc;
  if ((fdesc[0] != 'L') && (fdesc[0] != '[')) {
    if (fdesc[0] != vt) {
      jinn_assertion_fail(
        s, NULL, "The type of fieldID %p (%s) does not match the return type of %s.",
        finfo->fid, bda_jmethod_primitive_name(fdesc[0]), func_name);
      return 0;
    }
  } else {
    if (vt != 'O') {
      jinn_assertion_fail(
        s, NULL, "The type of fieldID %p (%s) does not match the return type of %s.",
        finfo->fid, fdesc, func_name);
      return 0;
    }
  }
  return 1;
}

static jclass bda_find_class_from_fdesc(JNIEnv *env, const char *fdesc)
{
  const char *cdesc;
  jclass clazz;
  cdesc = bda_str_dup_fdesc_to_cdesc(fdesc);
  clazz = bda_orig_jni_funcs->FindClass(env, cdesc);
  free((void*)cdesc);
  return clazz;
}

static int bda_check_field_type_setter(
    struct bda_state_info *s, 
    struct bda_field_info* finfo, 
    jclass oclass, 
    char vt, const jvalue v, const char *func_name)
{
  const char *fdesc;

  fdesc = finfo->fdesc;
  if ((fdesc[0] != 'L') && (fdesc[0] != '[')) {
    if (fdesc[0] != vt) {
      jinn_assertion_fail(
          s, NULL, "The type of fieldID %p does not match the target type of %s in %s.",
          finfo->fid, bda_jmethod_primitive_name(fdesc[0]), func_name);
      return 0;
    }
  } else {
    if (vt != 'O') {
      jinn_assertion_fail(
          s, NULL, "The type of fieldID %p does not match the target type of %s in %s.",
          finfo->fid, fdesc, func_name);
      return 0;
    } else if ( v.l != NULL ) {
      jclass fclass, vclass;
      jboolean assignable;
            
      fclass = bda_find_class_from_fdesc(s->env, fdesc);
      assert(fclass != NULL);
      vclass = bda_orig_jni_funcs->GetObjectClass(s->env, v.l);
      assert(vclass != NULL);
      assignable = bda_orig_jni_funcs->IsAssignableFrom(s->env, vclass, fclass);
      bda_orig_jni_funcs->DeleteLocalRef(s->env, fclass);
      bda_orig_jni_funcs->DeleteLocalRef(s->env, vclass);
      if (assignable != JNI_TRUE) {
        jinn_assertion_fail(
            s, NULL, "The type of fieldID %p (=%s) is not assignable to the target type (%s) in %s.",
            finfo->fid, fdesc, finfo->fdesc, func_name);
        return 0;
      }
    }
  }
  return 1;
}


int bda_check_jfieldid_to_reflected_field(
    struct bda_state_info *s, jclass c, jfieldID f, jboolean is_static, const char *fname)
{
  struct bda_field_info* finfo;
  int success;

  finfo = bda_jfieldID_lookup(s, c, f, is_static);
  if ((finfo == NULL) && (s->mode == SYS_NATIVE)) {
      return 1;
  }
  success = bda_check_field_common(s, finfo, f, c, is_static, fname);
  return success;
}

int bda_check_jfieldid_get_instance(
    struct bda_state_info *s, jobject o, jfieldID f, char vt, const char *func_name)
{
  jclass oclass;
  struct bda_field_info* finfo;
  int success;

  oclass = bda_orig_jni_funcs->GetObjectClass(s->env, o);
  assert(oclass != NULL);
  finfo = bda_jfieldID_lookup(s, oclass, f, JNI_FALSE);
  if ((finfo == NULL) && (s->mode == SYS_NATIVE)) {
      return 1;
  }
  success = bda_check_field_common(s, finfo, f, oclass, JNI_FALSE, func_name)
      && bda_check_field_type_getter(s, finfo, oclass, vt, func_name);
  bda_orig_jni_funcs->DeleteLocalRef(s->env, oclass);
  return success;
}

int bda_check_jfieldid_set_instance(struct bda_state_info *s, jobject o, jfieldID f, 
                                     const jvalue v, char vt, const char *func_name)
{
  struct bda_field_info *finfo;
  jclass oclass;
  int success;


  oclass = bda_orig_jni_funcs->GetObjectClass(s->env, o);
  assert(oclass != NULL);
  finfo = bda_jfieldID_lookup(s, oclass, f, JNI_FALSE);
  if ((finfo == NULL) && (s->mode == SYS_NATIVE)) {
      return 1;
  }

  success = bda_check_field_common(s, finfo, f, oclass, JNI_FALSE, func_name)
      && bda_check_field_type_setter(s, finfo, oclass, vt, v, func_name);
  bda_orig_jni_funcs->DeleteLocalRef(s->env, oclass);
  return success;
}

int bda_check_jfieldid_get_static(struct bda_state_info *s, jclass c, jfieldID f,  char vt, const char *func_name)
{
  struct bda_field_info *finfo;
  int success;

  finfo = bda_jfieldID_lookup(s, c, f, JNI_TRUE);
  if ((finfo == NULL) && (s->mode == SYS_NATIVE)) {
      return 1;
  }
  success = bda_check_field_common(s, finfo,  f,c, JNI_TRUE, func_name)
      && bda_check_field_type_getter(s, finfo, c, vt, func_name);
  return success;
}

int bda_check_jfieldid_set_static(struct bda_state_info *s, jclass c, jfieldID f, 
                                   const jvalue v, char vt, const char *func_name)
{
  struct bda_field_info *finfo;
  int success;

  finfo = bda_jfieldID_lookup(s, c, f, JNI_TRUE);
  if ((finfo == NULL) && (s->mode == SYS_NATIVE)) {
      return 1;
  }
  success = bda_check_field_common(s, finfo, f, c, JNI_TRUE, func_name) 
      && bda_check_field_type_setter(s, finfo, c, vt, v, func_name);
  return success;
}

static int bda_check_method_static(struct bda_state_info *s, 
                                   const struct bda_method_info * minfo,
                                   jmethodID mid, const char *func_name)
{
  if (minfo == NULL) {
    jinn_assertion_fail(s, NULL, "The method identifier %p not valid in %s.", mid, func_name);
    return 0;
  }
  assert(mid == minfo->mid);
  if (!minfo->is_static) {
      jinn_assertion_fail(s, NULL, "The method identifier %p is not static method in %s.", mid, func_name);
      return 0;
  }
  return 1;
}

static int bda_check_method_instance(struct bda_state_info *s, 
                                     const struct bda_method_info *minfo,
                                     jmethodID mid, const char *fname)
{
  if (minfo == NULL) {
    jinn_assertion_fail(s, NULL, "The method identifier %p is not valid in %s.", mid, fname);
    return 0;
  }
  assert(mid == minfo->mid);
  if (minfo->is_static) {
    jinn_assertion_fail(s, NULL, "The method identifier %p is not an instance method in %s.", mid, fname);
    return 0;
  }
  return 1;
}

static int bda_check_method_constructor(
    struct bda_state_info *s, const struct bda_method_info *minfo,
    const char *fname)
{
  int mname_ok, mdesc_ok;

  mname_ok = strcmp(minfo->mname, "<init>") == 0;
  mdesc_ok = minfo->returnType[0] == 'V';

  if (!mname_ok) {
    jinn_assertion_fail(
        s, NULL, "The constructor method %p doe not have its correct name, \"<init>\" in %s.", minfo->mid, fname);
    return 0;
  }

  if (!mdesc_ok) {
    jinn_assertion_fail(
        s, NULL, "The constructor method %p does not have void return type in %s.\n", minfo->mid, fname);
    return 0;
  }
  return 1;
}

static int bda_check_method_hierachy_equal(
    struct bda_state_info *s,  const struct bda_method_info *minfo,
    jclass clazz, const char *fname)
{
  jvmtiError err;
  jclass mclazz;
  jmethodID m = minfo->mid;
  jboolean same;

  err = (*bda_jvmti)->GetMethodDeclaringClass(bda_jvmti, m, &mclazz);
  assert (err == JVMTI_ERROR_NONE);
  same = bda_orig_jni_funcs->IsSameObject(s->env, clazz, mclazz)?JNI_TRUE:JNI_FALSE;
  bda_orig_jni_funcs->DeleteLocalRef(s->env, mclazz);
  if (same == JNI_FALSE) {
    jinn_assertion_fail(
        s, NULL, 
        "The declaring class of the method %p is not equal to the target class %p in %s.", 
        m, clazz, fname);
    return 0;
  }
  return 1;
}


static int bda_check_method_hierachy_superclass(
    struct bda_state_info *s,  const struct bda_method_info *minfo,
    jclass clazz, const char *fname)
{
  jvmtiError err;
  jclass mclazz;
  jmethodID m = minfo->mid;
  jboolean superclass;

  err = (*bda_jvmti)->GetMethodDeclaringClass(bda_jvmti, m, &mclazz);
  assert (err == JVMTI_ERROR_NONE);
  superclass = bda_orig_jni_funcs->IsAssignableFrom(s->env, clazz, mclazz);  
  if (!superclass) {
      jinn_assertion_fail(
          s, NULL, 
          "The declaring class of %p is not a super class of the target class %p in %s.", 
          m, clazz, fname);
      return 0;
  }
  return 1;
}

static int bda_check_method_hierachy_assignable(
    struct bda_state_info *s,  const struct bda_method_info *minfo,
    jclass clazz, const char *fname)
{
  jvmtiError err;
  jclass mclazz;
  jmethodID m = minfo->mid;
  jboolean assignable;

  err = (*bda_jvmti)->GetMethodDeclaringClass(bda_jvmti, m, &mclazz);
  assert (err == JVMTI_ERROR_NONE);
  assignable = bda_orig_jni_funcs->IsAssignableFrom(s->env, clazz, mclazz)?JNI_TRUE:JNI_FALSE;
  bda_orig_jni_funcs->DeleteLocalRef(s->env, mclazz);
  if (!assignable) {
    jinn_assertion_fail(
        s, NULL, 
        "The declaring class of method %p is not assignable to the target class %p in %s.", 
        m, clazz, fname);
    return 0;
  }
  return 1;
}

static int bda_check_method_hierachy_superclass_obj(
    struct bda_state_info *s,  const struct bda_method_info *minfo,
    jobject obj, const char *fname)
{
    int success;
    jclass obj_clazz = bda_orig_jni_funcs->GetObjectClass(s->env, obj);
    success = bda_check_method_hierachy_superclass(s, minfo, obj_clazz, fname);
    bda_orig_jni_funcs->DeleteLocalRef(s->env, obj_clazz);
    return success;
}

static int bda_check_method_hierachy_equals_obj(
    struct bda_state_info *s,  const struct bda_method_info *minfo,
    jobject obj, const char *fname)
{
    int success;
    jclass obj_clazz = bda_orig_jni_funcs->GetObjectClass(s->env, obj);
    success = bda_check_method_hierachy_equal(s, minfo, obj_clazz, fname);
    bda_orig_jni_funcs->DeleteLocalRef(s->env, obj_clazz);
    return success;
}

static int bda_check_method_hierachy_assignable_obj(
    struct bda_state_info *s,  const struct bda_method_info *minfo,
    jobject obj, const char *fname)
{
    int success;
    jclass obj_clazz = bda_orig_jni_funcs->GetObjectClass(s->env, obj);

    success = bda_check_method_hierachy_assignable(s, minfo, obj_clazz, fname);

    bda_orig_jni_funcs->DeleteLocalRef(s->env, obj_clazz);
    return success;
}

static int bda_check_method_arguments(
    struct bda_state_info *s,  const struct bda_method_info *minfo,
    struct bda_var_arg_wrap awrap, const char *fname)
{
  int index;
  const char **args;

  for(index = 0, args = minfo->argumentTypes; *args;args++, index++){
    const char *cdesc = *args;
    switch(cdesc[0]) {
    case 'B': case 'C': case 'I':  case 'S':case 'Z': case 'F':
      if (awrap.type == BDA_VA_LIST) {
          va_arg(awrap.value.ap, jint);
      }
      break;
    case 'D': case 'J' :
      if (awrap.type == BDA_VA_LIST) {
        va_arg(awrap.value.ap, jlong);
      }
      break;
    case 'L': case '[': {
      jobject object;
      if (awrap.type == BDA_VA_LIST) {
          object = va_arg(awrap.value.ap, jobject);
      } else {
          object = awrap.value.array[index].l;
      }
      if (object != NULL) {
        if (!bda_check_ref_dangling(s, object, index + 1, fname)) {
          return 0;
        } else {
          jclass clazz = bda_orig_jni_funcs->FindClass(s->env, cdesc);
          assert(clazz != NULL);
          if (! bda_check_assignable_jobject_jclass(s, object, clazz, index + 1, fname)){
              bda_orig_jni_funcs->DeleteLocalRef(s->env, clazz);
              return 0;
          } 
          bda_orig_jni_funcs->DeleteLocalRef(s->env, clazz);
        }
      }
    }
        break;
    default:
      assert(0);
      break;
    }
  }
  return 1;
}

static int bda_check_method_return_type(
    struct bda_state_info *s,  const struct bda_method_info *minfo, 
    char rt, const char *fname)
{
  if (rt == 'O') {
    if ((minfo->returnType[0] == 'L') || (minfo->returnType[0] == '[')) {
      return 1;
    } else {
      jinn_assertion_fail(
        s, NULL, "The return type mismatch in %s: method %p has return type: %s",
        fname, minfo->mid, minfo->mdesc);
      return 0;
    }
  } else {
    if (rt == minfo->returnType[0]) {
      return 1;
    } else {
      jinn_assertion_fail(
        s, NULL, "The return type mismatch in %s: method %p has return type: %s",
        fname, minfo->mid, minfo->mdesc);
      return 0;
    }
  }
}

static int bda_check_method_is_private_or_constructor(
    struct bda_state_info *s,  const struct bda_method_info *minfo)
{
  jint fmodifier;
  jvmtiError err;
  int result = 0;
  jmethodID m = minfo->mid;

  err = (*bda_jvmti)->GetMethodModifiers(bda_jvmti, m, &fmodifier);
  assert(err == JVMTI_ERROR_NONE);
  if ((fmodifier & JVM_ACC_PRIVATE) == JVM_ACC_PRIVATE) {
      result = 1;
  } else {
      char *mname, *mdesc;
      int mdesc_len;

      err = (*bda_jvmti)->GetMethodName(bda_jvmti, m, &mname, &mdesc, NULL);
      assert(err == JVMTI_ERROR_NONE);
      if (strcmp(mname, "<init>")  == 0) {
          mdesc_len = strlen(mdesc);        
          if ((mdesc_len >= 3) && (mname[mdesc_len - 2] == ')') && (mname[mdesc_len -1] = 'V' )) {
              result = 1;
          }
      }
      (*bda_jvmti)->Deallocate(bda_jvmti, (unsigned char*)mname);
      (*bda_jvmti)->Deallocate(bda_jvmti, (unsigned char*)mdesc);
  }

  return result;
}


static jboolean bda_is_array(JNIEnv *env, jobject obj) {
  jboolean is_array;
  jclass ref_class;
  jvmtiError err;

  ref_class = bda_orig_jni_funcs->GetObjectClass(env, obj);
  err =(*bda_jvmti)->IsArrayClass(bda_jvmti, ref_class, &is_array);
  assert(err == JVMTI_ERROR_NONE);
  bda_orig_jni_funcs->DeleteLocalRef(env, ref_class);

  return is_array;
}

int bda_check_jmethodid_to_reflected(struct bda_state_info *s, jclass c, jmethodID m, jboolean b, const char *fname)
{
  return 0;
}

int bda_check_jmethodid_new_object(struct bda_state_info *s, jclass clazz, 
                                    jmethodID m, struct bda_var_arg_wrap args, 
                                    const char *fname)
{
  const struct bda_method_info *minfo;

  minfo = bda_method_info_lookup(m);
  if ((minfo == NULL) && (s->mode == SYS_NATIVE)) {return 1;}

  return  bda_check_method_instance(s, minfo, m, fname)
      && bda_check_method_constructor(s, minfo, fname)
      && bda_check_method_hierachy_equal(s, minfo, clazz, fname)
      && bda_check_method_arguments(s, minfo, args, fname);
}

int bda_check_jmethodid_instance(struct bda_state_info *s, jobject obj, 
                                  jmethodID mid, struct bda_var_arg_wrap args, 
                                  const char *fname, char rt)
{
  const struct bda_method_info *minfo;
  
  minfo = bda_method_info_lookup(mid);
  if ((minfo == NULL) && (s->mode == SYS_NATIVE)) {return 1;}

  if (bda_check_method_is_private_or_constructor(s, minfo)) {
      return bda_check_method_instance(s, minfo, mid, fname)
          && bda_check_method_hierachy_equals_obj(s, minfo, obj, fname)
          && bda_check_method_return_type(s, minfo, rt, fname)
          && bda_check_method_arguments(s, minfo, args, fname);
  } else {
      return bda_check_method_instance(s, minfo, mid, fname)
          && bda_check_method_hierachy_assignable_obj(s, minfo, obj, fname)
          && bda_check_method_return_type(s, minfo, rt, fname)
          && bda_check_method_arguments(s, minfo, args, fname);
  }
}

int bda_check_jmethodid_nonvirtual(struct bda_state_info *s, jobject obj, 
                                    jclass clazz, jmethodID mid, 
                                    struct bda_var_arg_wrap args, 
                                    const char *fname, char rt)
{
  const struct bda_method_info *minfo;

  minfo = bda_method_info_lookup(mid);
  if ((minfo == NULL) && (s->mode == SYS_NATIVE)) {return 1;}

  return bda_check_method_instance(s, minfo, mid, fname)
      && bda_check_method_hierachy_superclass(s, minfo, clazz, fname)
      && bda_check_method_hierachy_superclass_obj(s, minfo, obj, fname)
      && bda_check_method_arguments(s, minfo, args, fname)
      && bda_check_method_return_type(s, minfo, rt, fname);
}

int bda_check_jmethodid_static(struct bda_state_info *s, jclass clazz, 
                                jmethodID methodID, struct bda_var_arg_wrap args, 
                                const char *fname, char rt)
{
  const struct bda_method_info *minfo;

  minfo = bda_method_info_lookup(methodID);
  if ((minfo == NULL) && (s->mode == SYS_NATIVE)) {return 1;}

  return bda_check_method_static(s, minfo, methodID, fname)
      && bda_check_method_hierachy_equal(s, minfo, clazz, fname)
      && bda_check_method_return_type(s, minfo, rt, fname)
      && bda_check_method_arguments(s, minfo, args, fname);
}

int bda_check_ref_dangling(struct bda_state_info *s,  jobject obj, int index, const char *fname) {
  if ((obj != NULL) &&!bda_check_live(s, obj)) {
      if (s->mode != USR_NATIVE) {
          /* kludge: bypass dangling reference checking in classpath
           * library. Hotspot classpath native code seems to use internal
           * language transition from C to JVM. Just assume that classpath
           * native code is correct.*/
          return 1;
      } else {
          jinn_assertion_fail(
              s, NULL, "The JNI reference %p is dead in the argument %d of %s.", obj, index + 1, fname);
          return 0;
      }
  }
  return 1;
}

int bda_check_jclass(struct bda_state_info *s, jclass clazz, int index, const char *fname)
{
    return (clazz != NULL) && 
     bda_check_instance_jobject_jclass(s, clazz, bda_clazz_class, index, fname);
}

int bda_check_jstring(struct bda_state_info *s, jstring jstr, int index, const char *fname)
{
    return (jstr != NULL) && bda_check_instance_jobject_jclass(s, jstr, bda_clazz_string, index, fname);
}

int bda_check_jthrowable(struct bda_state_info *s, jthrowable t, int index, const char *fname)
{
  return (t != NULL) && bda_check_assignable_jobject_jclass(s, t, bda_clazz_throwable, index, fname);
}

int bda_check_jweak(struct bda_state_info *s, jweak ref, int index, const char *fname)
{  
  return (ref != NULL) &&
      bda_check_jobject_ref_type(s, ref, JNIWeakGlobalRefType, index, fname);
}

int bda_check_jarray(struct bda_state_info *s, jarray ref, int index, const char *fname)
{
  if (ref == NULL) {return 1;}

  if (!bda_is_array(s->env, ref)) {
    jinn_assertion_fail(
        s, NULL, 
        "The JNI reference %p is not an array object in the argument %d of %s.", 
        ref, index, fname);
    return 0;
  }
  return 1;
}

int bda_check_jbooleanArray(struct bda_state_info *s, jbooleanArray ref, int index, const char *fname)
{
    return bda_check_jarray(s, ref, index, fname)  &&
      bda_check_instance_jobject_jclass(s, ref, bda_clazz_booleanArray, index, fname);
}

int bda_check_jbyteArray(struct bda_state_info *s, jbyteArray ref, int index, const char *fname)
{
    return (ref != NULL) && bda_check_jarray(s, ref, index, fname) &&
        bda_check_instance_jobject_jclass(s, ref, bda_clazz_byteArray,index, fname);
}

int bda_check_jcharArray(struct bda_state_info *s, jcharArray ref, int index, const char *fname)
{
  return (ref != NULL) && bda_check_jarray(s, ref, index, fname) &&
      bda_check_instance_jobject_jclass(s, ref, bda_clazz_charArray,index, fname);  
}

int bda_check_jshortArray(struct bda_state_info *s, jshortArray ref, int index, const char *fname)
{
  return (ref != NULL) && bda_check_jarray(s, ref, index, fname) &&
      bda_check_instance_jobject_jclass(s, ref, bda_clazz_shortArray,index, fname);  
}

int bda_check_jintArray(struct bda_state_info *s, jintArray ref, int index, const char *fname)
{
  return (ref != NULL) && bda_check_jarray(s, ref, index, fname) &&
      bda_check_instance_jobject_jclass(s, ref, bda_clazz_intArray,index, fname);  
}

int bda_check_jlongArray(struct bda_state_info *s, jlongArray ref, int index, const char *fname)
{
  return (ref != NULL) && bda_check_jarray(s, ref, index, fname) &&
      bda_check_instance_jobject_jclass(s, ref, bda_clazz_longArray,index, fname);  
}

int bda_check_jfloatArray(struct bda_state_info *s, jfloatArray ref, int index, const char *fname)
{
    return (ref != NULL) && bda_check_jarray(s, ref, index, fname) &&
      bda_check_instance_jobject_jclass(s, ref, bda_clazz_floatArray,index, fname);  
}

int bda_check_jdoubleArray(struct bda_state_info *s, jdoubleArray ref, int index, const char *fname)
{
    return (ref != NULL) && bda_check_jarray(s, ref, index, fname) &&
      bda_check_instance_jobject_jclass(s, ref, bda_clazz_doubleArray,index, fname);  
}

int bda_check_jobjectArray(struct bda_state_info *s, jobjectArray ref, int index, const char *fname)
{
  jvmtiError err;
  jclass ref_class;
  char *cdesc;
  int is_object_array;

  if (ref == NULL) {return 1;}
  if (!bda_check_jarray(s, ref, index, fname)) {return 0;}

  ref_class = bda_orig_jni_funcs->GetObjectClass(s->env, ref);
  err = (*bda_jvmti)->GetClassSignature(bda_jvmti, ref_class, &cdesc, NULL);
  assert(err == JVMTI_ERROR_NONE);
  is_object_array = (cdesc[0] == '[') && ((cdesc[1] == 'L') || (cdesc[1] == '['));
  bda_orig_jni_funcs->DeleteLocalRef(s->env, ref_class);
  err = (*bda_jvmti)->Deallocate(bda_jvmti, (unsigned char *)cdesc);
  assert(err == JVMTI_ERROR_NONE);

  if (!is_object_array) {
    jinn_assertion_fail(
        s, NULL, "The JNI reference %p is not an object array in the argument %d of %s.", ref, index, fname);
    return 0;
  }
  return 1;
}

int bda_check_instance_jobject_jclass(
    struct bda_state_info *s, jobject obj, jclass o_class, int index, const char *fname)
{
  jclass ref_class;
  jboolean is_same;

  if (obj == NULL) {return 1;}

  ref_class = bda_orig_jni_funcs->GetObjectClass(s->env, obj);
  is_same = bda_orig_jni_funcs->IsSameObject(s->env, ref_class, o_class);
  bda_orig_jni_funcs->DeleteLocalRef(s->env, ref_class);

  if (is_same == JNI_FALSE) {
    jinn_assertion_fail(
        s, NULL, "The JNI reference %p is not an instance of the class %p in the argument %d of %s.", 
        obj, o_class, index + 1, fname);
    return 0;
  }
  return 1;
}


int bda_check_assignable_jclass_jclass(
    struct bda_state_info *s, jclass clazz, jclass sup_clazz, int index, const char *fname)
{
  jboolean is_assignable_class;

  if (clazz == NULL) {return 1;}
  is_assignable_class = bda_orig_jni_funcs->IsAssignableFrom(s->env, clazz, sup_clazz);

  if (!is_assignable_class) {
    jinn_assertion_fail(
        s, NULL, "The JNI reference %p is not an ancestor of the class %p in the argument %d of %s.", 
        sup_clazz, clazz, index + 1, fname);
    return 0;
  }
  return 1;
}


int bda_check_assignable_jobject_jclass(
    struct bda_state_info *s, jobject obj, jclass sup_clazz, int index, const char *fname)
{
  jclass sub_clazz;
  jboolean is_assignable_class;

  if (obj == NULL) {return 1;}
  sub_clazz = bda_orig_jni_funcs->GetObjectClass(s->env, obj);
  is_assignable_class =  bda_orig_jni_funcs->IsAssignableFrom(s->env, sub_clazz, sup_clazz);
  bda_orig_jni_funcs->DeleteLocalRef(s->env, sub_clazz);

  if (!is_assignable_class) {
    jinn_assertion_fail(
        s, NULL, "The class of the object %p is not an ancestor of the class %p in the argument %d of %s.", 
        obj, sup_clazz, index + 1, fname);
    return 0;
  }
  return 1;
}


int bda_check_assignable_jclass_jobject(
    struct bda_state_info *s, jclass clazz, jobject obj, int index, const char *fname)
{
  jclass source_class;
  jboolean is_assignable;

  if (obj == NULL) {return 1;}
  source_class = bda_orig_jni_funcs->GetObjectClass(s->env, obj);
  is_assignable = bda_orig_jni_funcs->IsAssignableFrom(s->env, source_class, clazz);
  bda_orig_jni_funcs->DeleteLocalRef(s->env, source_class);

  if (!is_assignable) {
      jinn_assertion_fail(
          s, NULL, "The object %p is not assignable to %p in the argument %d of %s.",
          obj, clazz, index  + 1, fname);
      return 0;
  }
  return 1;
}

const char *bda_get_ref_type_name(jobjectRefType ref_type)
{
  switch(ref_type){
  case JNIInvalidRefType: return "invalid";
  case JNILocalRefType: return "local";
  case JNIGlobalRefType: return "global";
  case JNIWeakGlobalRefType:return "weak global";
  default: assert(0); return "";
  }
}

int bda_check_jobject_ref_type(
    struct bda_state_info *s, jobject obj, jobjectRefType expected_ref_type, int index, const char *fname)
{
  int success = 0;

  /* 
   * "Deletes the global reference pointed to by gref. The gref
   * argument must be a global reference, or NULL. The same non-NULL
   * global reference must not be deleted more than once. Deleting a
   * NULL global reference is a no-op."
   * [http://java.sun.com/docs/books/jni/html/functions.html#64717]
   */
  if (obj == NULL) {
    return 1;
  }

  switch(expected_ref_type) {
  case JNIInvalidRefType:
      assert(0);
      break;
  case JNILocalRefType: {
    struct bda_local_frame * frame;
    int i;
    for (frame = s->local_frame_top; frame != NULL; frame = frame->next){
        for(i = frame->count - 1; i >= 0;i--) {
            if (frame->list[i] == obj) {
                success = 1;
            }
        }
    }
    break;
  }
  case JNIGlobalRefType:
      MUTEX_LOCK(bda_global_resources_lock);
      success = htable_get(bda_global_ref_table, (void*)obj) == obj;
      MUTEX_UNLOCK(bda_global_resources_lock);
      break;
  case JNIWeakGlobalRefType:
      MUTEX_LOCK(bda_global_resources_lock);
      success = htable_get(bda_weak_global_ref_table, (void*)obj) == obj;
      MUTEX_UNLOCK(bda_global_resources_lock);
      break;
  }

  if (!success && s->mode == USR_NATIVE) {
    jinn_assertion_fail(
        s, NULL, "The JNI reference %p is not a %s reference in the argument %d of %s.", 
        obj, bda_get_ref_type_name(expected_ref_type), index + 1, fname);
    return 0;
  }
  return 1;
}

int bda_check_assignable_jobjectArray_jobject(
    struct bda_state_info *s, jobjectArray array, jobject obj, int index, const char *fname)
{
  char *cdesc;
  jclass array_clazz, element_clazz, obj_clazz;
  jboolean assignable;
  jvmtiError err;
  char *element_desc;
  int len_cdesc;

  array_clazz = bda_orig_jni_funcs->GetObjectClass(s->env, array);
  err = (*bda_jvmti)->GetClassSignature(bda_jvmti, array_clazz, &cdesc, NULL);
  assert(err == JVMTI_ERROR_NONE);
  bda_orig_jni_funcs->DeleteLocalRef(s->env, array_clazz);

  len_cdesc=strlen(cdesc);
  element_desc=malloc(len_cdesc+1);
  assert(len_cdesc >= 3);
  assert(cdesc[0] == '[');
  if (cdesc[1] == '[') {
      memcpy(element_desc, &cdesc[1], len_cdesc);
  } else {
      assert(cdesc[1] == 'L');
      memcpy(element_desc, &cdesc[2], len_cdesc - 3);
      element_desc[len_cdesc - 3] = '\0';
  }

  element_clazz = bda_orig_jni_funcs->FindClass(s->env, element_desc);
  err = (*bda_jvmti)->Deallocate(bda_jvmti, (unsigned char*)cdesc);
  assert(err == JVMTI_ERROR_NONE);
  free(element_desc);

  obj_clazz = bda_orig_jni_funcs->GetObjectClass(s->env, obj);
  assignable = bda_orig_jni_funcs->IsAssignableFrom(s->env, obj_clazz, element_clazz);
  bda_orig_jni_funcs->DeleteLocalRef(s->env, element_clazz);
  bda_orig_jni_funcs->DeleteLocalRef(s->env, obj_clazz);

  if (!assignable) {
    jinn_assertion_fail(
        s, NULL, "The object %p is not assignable to the array %p in the argument %d of %s.",
        obj, array, index + 1, fname);
    return 0;
  }
  return 1;
}

int bda_check_jclass_scalar_allocatable(struct bda_state_info *s, jclass clazz, int index, const char *fname)
{
  jint modifier;
  jboolean is_array;
  jvmtiError err;

  err = (*bda_jvmti)->GetClassModifiers(bda_jvmti, clazz, &modifier);
  assert(err == JVMTI_ERROR_NONE);
  err =(*bda_jvmti)->IsArrayClass(bda_jvmti, clazz, &is_array);
  assert(err == JVMTI_ERROR_NONE);

  if (is_array || (modifier&JVM_ACC_INTERFACE) || (modifier & JVM_ACC_ABSTRACT)) {
    jinn_assertion_fail(
        s, NULL, "The class %p is not scalar class in the argument %d of %s.",
        clazz, index + 1, fname);
    return 0;
  }
  return 1;
}

int bda_check_jarray_primitive(struct bda_state_info *s, jarray array, int index, const char *fname)
{
  char *cdesc;
  int is_primitive_array;
  jclass clazz;
  jvmtiError err;

  clazz = bda_orig_jni_funcs->GetObjectClass(s->env, array);
  err = (*bda_jvmti)->GetClassSignature(bda_jvmti, clazz, &cdesc, NULL);
  assert(err == JVMTI_ERROR_NONE);
  assert(cdesc[0] == '[');
  bda_orig_jni_funcs->DeleteLocalRef(s->env, clazz);

  is_primitive_array = 0;  
  if (cdesc[2] == '\0') {
      switch(cdesc[1]) {
      case 'Z':case 'B':case 'C':case 'S':case 'I':case 'J':case 'F':case 'D':
          is_primitive_array = 1;
          break;
      }
  }

  if (!is_primitive_array) {
    jinn_assertion_fail(s, NULL, 
                   "The JNI reference %p is not a primitive array in the argument %d of %s.",
                   array, index + 1, fname);
    return 0;
  }
  return 1;
}

int bda_check_jobject_reflected_method(struct bda_state_info *s, jobject obj, int index, const char *fname)
{
  return bda_check_instance_jobject_jclass(s, obj, bda_clazz_method,index, fname)
      && bda_check_instance_jobject_jclass(s, obj, bda_clazz_constructor,index, fname);
}

int bda_check_local_frame_double_free(struct bda_state_info *s)
{
  struct bda_local_frame * top_frame;

  top_frame = s->local_frame_top;
  if ((top_frame == NULL) || (top_frame->sentinel)) {
    jinn_assertion_fail(
        s, NULL, "Error: double-free where local frame can not be poped up.");
    return 0;
  }

  return 1;
}

int bda_check_local_frame_leak(struct bda_state_info *s)
{
  struct bda_local_frame * top_frame;

  top_frame = s->local_frame_top;
  if ((top_frame == NULL) || (!top_frame->sentinel)) {
      jinn_assertion_fail(
          s, NULL, "Error: leak where local frame is not empty.");
      return 0;
  } else {
      return 1;
  }    
}

int bda_check_local_frame_overflow(struct bda_state_info *s, const char *fname)
{
  struct bda_local_frame * top_frame;

  top_frame = s->local_frame_top;
  if (top_frame->count >= top_frame->capacity) {
    int i;
    jobject * new_list;
    jinn_assertion_fail(
        s, NULL, "The number of local references exceeds the current capacity %d in %s.", 
        top_frame->capacity, fname);

    /* double the capacity. */
    new_list =  (jobject *)calloc(top_frame->capacity * 2, sizeof(jobject));
    assert(new_list != NULL);
    for(i=0; i < top_frame->count;i++) {
      new_list[i] = top_frame->list[i];
    }
    free(top_frame->list);
    top_frame->capacity = top_frame->capacity * 2;
    top_frame->list = new_list;
    return 0;
  }

  return 1;
}

int bda_check_access_set_instance_field(
    struct bda_state_info *s, jobject o, jfieldID fid, int index, const char *fname)
{
  struct bda_field_info *i;
  jclass clazz;

  clazz = bda_orig_jni_funcs->GetObjectClass(s->env, o);
  i = bda_jfieldID_lookup(s, clazz, fid, JNI_FALSE);
  bda_orig_jni_funcs->DeleteLocalRef(s->env, clazz);

  if ((i != NULL) && ((i->modifier & JVM_ACC_FINAL) == JVM_ACC_FINAL) && !(i->mutable_final)) {
    jinn_assertion_fail(
        s, NULL, "The field %p is final in the argument %d of %s.", fid, index + 1, fname);
    return 0;
  }

  return 1;
}

int bda_check_access_set_static_field(
    struct bda_state_info *s, jclass c, jfieldID fid, int index, const char *fname)
{
  struct bda_field_info *i;

  i = bda_jfieldID_lookup(s, c, fid, JNI_TRUE);
  if ((i != NULL) && ((i->modifier & JVM_ACC_FINAL) == JVM_ACC_FINAL) && !(i->mutable_final)) {
    jinn_assertion_fail(
        s, NULL, "The field %p is final in the argument %d of %s.", fid, index, fname);
    return 0;
  }

  return 1;
}

void bda_resource_acquire(struct bda_state_info *s, const void *resource, const char *fname)
{
  MUTEX_LOCK(bda_global_resources_lock);
  htable_put(bda_resource_table, (void*)resource, (void*)fname);
  MUTEX_UNLOCK(bda_global_resources_lock);
}

void bda_resource_release(struct bda_state_info *s, const void *resource, const char *fname)
{
  MUTEX_LOCK(bda_global_resources_lock);
  htable_remove(bda_resource_table, (void*)resource);
  MUTEX_UNLOCK(bda_global_resources_lock);
}

int bda_check_resource_free(struct bda_state_info *s, const void *resource, const char *fname)
{
  const char *found;

  MUTEX_LOCK(bda_global_resources_lock);
  found = (const char *)htable_get(bda_resource_table, (void *)resource);
  MUTEX_UNLOCK(bda_global_resources_lock);
  if (!found) {
    jinn_assertion_fail(
        s, NULL, "%s -- VM resource %p is not active.", fname, resource);
    return 0;
  }
  return 1;
}

int bda_check_resource_leak(JNIEnv *env)
{
    MUTEX_LOCK(bda_global_resources_lock);
    if (htable_count(bda_resource_table) > 0 ) {
        int i;
        struct hentry *e;
    
        printf("The following VM resoures are not released.\n");
        printf("%10s   %20s\n", "resource", "allocator");
        for(i=0; i < HTABLE_BUCKET_SIZE;i++)
            for(e=bda_resource_table->buckets[i];e != NULL;e=e->next) {
                const void *resource = e->key;
                const char *fname = e->value;
                printf("%10p   %20s\n", resource, fname);
            }
        MUTEX_UNLOCK(bda_global_resources_lock);
        return 0;
    }
    MUTEX_UNLOCK(bda_global_resources_lock);
    return 1;
}

int bda_check_no_critical(struct bda_state_info *s, const char *fname)
{
    if (s->critical != 0 ) {
        jinn_assertion_fail(
            s, NULL, "The current thread is in JNI critical region in %s.", fname);
        return 0;
    }
    return 1;
}

void bda_enter_critical(struct bda_state_info *s, void *cptr)
{
  int *count;
  count = (int *)htable_get(s->open_criticals, cptr);
  if (count == NULL) {
      count = (int*)malloc(sizeof(int));
      htable_put(s->open_criticals, cptr, count);
  }
  *count = *count + 1;
  s->critical++;
}

void bda_leave_critical(struct bda_state_info *s, void *cptr)
{
  int *count;
  
  count = (int *)htable_get(s->open_criticals, cptr);
  if (count != NULL) {
    *count = *count - 1;
    if (*count == 0) {
      htable_remove(s->open_criticals, cptr);
      free(count);
    }
    s->critical--;
  } else {
    assert(0);
  }
}


void bda_monitor_enter(struct bda_state_info *s, jobject o)
{
    JNIEnv *env = s->env;
    struct bda_monitor_state *curr;

    /* Try to find active monitor object. */
    for(curr = bda_monitor_state_head;curr != NULL;curr = curr->next) {
        if (bda_orig_jni_funcs->IsSameObject(env, o, curr->object)) {
            curr->count = curr->count + 1;
            return;
        }
    }

    /* Add a new entry. */
    curr = malloc(sizeof(struct bda_monitor_state));
    curr->object = (*env)->NewGlobalRef(env, o);
    curr->count = 1;
    
    curr->next = bda_monitor_state_head;
    bda_monitor_state_head = curr;
}

void bda_monitor_exit(struct bda_state_info *s, jobject o)
{
    JNIEnv *env = s->env;
    struct bda_monitor_state *curr;
    struct bda_monitor_state *prev;
    
   /* Try to find active monitor object. */
    prev = NULL;
    curr = bda_monitor_state_head;
    while(curr != NULL) {
        if (bda_orig_jni_funcs->IsSameObject(env, o, curr->object)) {
            curr->count = curr->count - 1;
            if (curr->count == 0) {
                bda_orig_jni_funcs->DeleteGlobalRef(env, o);
                /* Delete the element. */
                if (prev == NULL) {
                    bda_monitor_state_head = curr->next;
                } else {
                    prev->next = curr->next;
                }
                free(curr);
            }
        }
        prev = curr;
        curr = prev->next;
    }
}

int bda_check_monitor_leak(JNIEnv *env)
{
    struct bda_monitor_state *curr;

    if (bda_monitor_state_head != NULL) {
        printf("The following Java monitors are not released.\n");
        for(curr = bda_monitor_state_head; curr != NULL;curr = curr->next) {
            printf("global ref = %p count = %d\n", curr->object, curr->count);
            return 0;
        }
    }
    return 1;
}
