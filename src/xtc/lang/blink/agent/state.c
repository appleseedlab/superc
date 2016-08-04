#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <jvmti.h>
#include <stdlib.h>

#include "agent_main.h"
#include "options.h"
#include "state.h"
#include "agent.h"
#include "util.h"
#include "jnicheck.h"

#define OPCODE_INVOKE_VIRTUAL (0xb6) 
#define OPCODE_INVOKE_SPECIAL (0xb7)
#define OPCODE_INVOKE_STATIC  (0xb8)
#define OPCODE_INVOKE_INTERFACE (0xb9)

static void bda_set_java_location(
    jvmtiEnv *jvmti, jmethodID mid, 
    struct bda_location *jloc);

static int bda_get_line_number(
    jvmtiEnv *jvmti, jmethodID method, jlocation jloc);

TLS_TYPE_SPEC struct bda_state_info *bda_tls_state = NULL;

struct bda_state_info *bda_tls_state_get()
{
    return bda_tls_state;
}

static void bda_init_location(struct bda_location *loc)
{
    loc->native_address = 0;
    loc->cname = NULL;
    loc->mname = NULL;
    loc->mdesc = NULL;
    loc->line_number = 0;
    loc->bcindex = -1;
}

static int bda_get_line_number(
    jvmtiEnv *jvmti, 
    jmethodID method,
    jlocation jloc)
{
    jvmtiError err;
    jvmtiLineNumberEntry* line_number_table;
    jint num_entries_line_number_table;
    int line_number, i;

    err = (*jvmti)->GetLineNumberTable(jvmti, method, 
                                       &num_entries_line_number_table,
                                       &line_number_table);
    if (err == JVMTI_ERROR_ABSENT_INFORMATION) {
        return 0;
    }
    assert(err == JVMTI_ERROR_NONE);
    for(i=0;i < num_entries_line_number_table;i++) {
        jlocation start_loc = line_number_table[i].start_location;
        if (start_loc > jloc) {
            break;
        }
    }
    assert(i>=1);
    line_number = line_number_table[i-1].line_number;

    err = (*jvmti)->Deallocate(jvmti, (unsigned char*)line_number_table);
    assert(err == JVMTI_ERROR_NONE);

    return line_number;
}

static void bda_release_location(struct bda_location *jloc)
{
    if (!jloc->cname)
        free((void *)jloc->cname);
    if (!jloc->mname)
        free((void *)jloc->mname);
    if (!jloc->mdesc)
        free((void *)jloc->mdesc);
}

static int bda_method_name_and_desc_match(jvmtiEnv *jvmti, jmethodID m1, jmethodID m2)
{
    jvmtiError err;
    char *mname1, *mdesc1;
    char *mname2, *mdesc2;
    int result;

    err = (*jvmti)->GetMethodName(jvmti, m1, &mname1, &mdesc1, NULL);
    assert(err == JVMTI_ERROR_NONE);
    err = (*jvmti)->GetMethodName(jvmti, m2, &mname2, &mdesc2, NULL);
    assert(err == JVMTI_ERROR_NONE);

    result = (0 == strcmp(mname1, mname2)) && (0 == strcmp(mdesc1, mdesc2));

    err = (*jvmti)->Deallocate(jvmti, (unsigned char *) mname1);
    assert(err == JVMTI_ERROR_NONE);
    err = (*jvmti)->Deallocate(jvmti, (unsigned char *) mdesc1);
    assert(err == JVMTI_ERROR_NONE);

    err = (*jvmti)->Deallocate(jvmti, (unsigned char *) mname2);
    assert(err == JVMTI_ERROR_NONE);
    err = (*jvmti)->Deallocate(jvmti, (unsigned char *) mdesc2);
    assert(err == JVMTI_ERROR_NONE);
    
    return result;
}

static const char *bda_cdesc2cname(const char *cdesc)
{
    int i,j;
    char *cname;

    cname=malloc(strlen(cdesc) + 1);
    assert(cdesc[0] == 'L');
    for(i=1,j=0; cdesc[i] != '\0' && cdesc[i] != ';';i++,j++) {
        if (cdesc[i] == '/') {
            cname[j] = '.';
        } else {
            cname[j] = cdesc[i];
        }
    }
    cname[j] = '\0';
    return (const char *)cname;
}

static void bda_get_return_location(
    jvmtiEnv *jvmti, struct bda_location *loc)
{
    jvmtiError err;
    jvmtiFrameInfo frames[5];
    jint fcount; 
    jmethodID method;
    jlocation bcindex_call, bcindex_return;
    jlocation bcindex_start, bcindex_end;
    int line_number;
    int i;
    unsigned char *bytecodes;
    jint bytecodes_size;

    //find the most recent java frame.
    assert(jvmti != NULL);
    err = (*jvmti)->GetStackTrace(jvmti, NULL, 0, 5, frames, &fcount);
    assert(err == JVMTI_ERROR_NONE);
    method = NULL;
    for(i=0; i < fcount;i++) {
        jboolean is_native;
        err = (*jvmti)->IsMethodNative(jvmti, frames[i].method, &is_native);
        assert(err == JVMTI_ERROR_NONE);
        if (!is_native) {
            method = frames[i].method;
            bcindex_call = frames[i].location;
            break;
        }
    }
    assert(method != NULL);

    bda_set_java_location(jvmti, method, loc);
    err = (*jvmti)->GetMethodLocation(jvmti, method, &bcindex_start, &bcindex_end);
    assert(err == JVMTI_ERROR_NONE);
    err = (*jvmti)->GetBytecodes(jvmti, method, &bytecodes_size, &bytecodes);
    assert(err == JVMTI_ERROR_NONE);
    //now decode the byte code to get the next line number.
    switch(bytecodes[bcindex_call - bcindex_start]) {
    case OPCODE_INVOKE_VIRTUAL:
    case OPCODE_INVOKE_SPECIAL:
    case OPCODE_INVOKE_STATIC:
        bcindex_return = bcindex_call + 3;
        break;
    case OPCODE_INVOKE_INTERFACE:
        bcindex_return = bcindex_call + 5;
        break;
    default:
        assert(0); /*not call instruct at the call site?.*/
        break;
    }
    line_number = bda_get_line_number(jvmti, method, bcindex_return);
    loc->bcindex = bcindex_return;
    loc->line_number = line_number;
}

static void bda_set_java_location(jvmtiEnv *jvmti, jmethodID mid, 
                           struct bda_location *jloc) 
{
    jvmtiError err;
    char *cdesc, *mname, *mdesc;
    jclass clazz;
    jlocation start, end;

    err = (*jvmti)->GetMethodDeclaringClass(jvmti, mid, &clazz);
    assert(err == JVMTI_ERROR_NONE);
    err = (*jvmti)->GetClassSignature(jvmti, clazz, &cdesc, NULL);
    assert(err == JVMTI_ERROR_NONE);
    err = (*jvmti)->GetMethodName(jvmti, mid, &mname, &mdesc, NULL);
    assert(err == JVMTI_ERROR_NONE);
    err = (*jvmti)->GetMethodLocation(jvmti, mid, &start, &end);
    assert(err == JVMTI_ERROR_NONE);

    jloc->cname = bda_cdesc2cname(cdesc);
    jloc->mname= strdup(mname);
    jloc->mdesc = strdup(mdesc);
    jloc->bcindex = 0;
    jloc->line_number = bda_get_line_number(jvmti, mid, start);
    
    err = (*jvmti)->Deallocate(jvmti, (unsigned char *) cdesc);
    assert(err == JVMTI_ERROR_NONE);
    err = (*jvmti)->Deallocate(jvmti,(unsigned char *) mname);
    assert(err == JVMTI_ERROR_NONE);
    err = (*jvmti)->Deallocate(jvmti, (unsigned char *) mdesc);
    assert(err == JVMTI_ERROR_NONE);
}


static void bda_get_c2j_target(
    struct bda_state_info *s, 
    struct bda_jni_function_frame *frame,
    struct bda_location *jloc)
{
    enum bda_c2j_call_type c2j_type = frame->call_type;
    JNIEnv *env = s->env;
    jclass clazz = frame->class;
    jobject obj = frame->object;
    jmethodID mid = frame->mid;

    switch(c2j_type) {
    case JNI_CALL_STATIC: {
        bda_set_java_location(bda_jvmti, mid, jloc);
        break;
    }
    case JNI_CALL_INSTANCE: {
        jvmtiError err;
        jmethodID target_method;
        jclass target_clazz;

        assert(clazz == NULL);
        clazz = bda_orig_jni_funcs->GetObjectClass(env, obj);
        assert(clazz != NULL);

        //search for the actual target virtual method.
        target_method = NULL;
        target_clazz = clazz;
        while (target_clazz != NULL && (target_method == NULL)) {
            jint method_count;
            jmethodID* methods;
            int i;

            err = (*bda_jvmti)->GetClassMethods(bda_jvmti, target_clazz, 
                                                &method_count, &methods);
            assert(err == JVMTI_ERROR_NONE);
            for(i=0;i < method_count;i++) {
                if(bda_method_name_and_desc_match(bda_jvmti, mid, methods[i])) {
                    target_method = methods[i];
                    break;
                }
            }
            (*bda_jvmti)->Deallocate(bda_jvmti, (unsigned char *)methods);

            if (target_method == NULL) {
                target_clazz = bda_orig_jni_funcs->GetSuperclass(env, target_clazz);
            }
        }
        assert(target_method != NULL);
        bda_set_java_location(bda_jvmti, target_method, jloc);
        break;
    }
    case JNI_CALL_NONVIRTUAL: {
        bda_set_java_location(bda_jvmti, mid, jloc);
        break;
    }
    default:
        assert(0); /* not reachable. */
        break;
    }
}


struct bda_state_info *bda_state_allocate(JNIEnv *env)
{
  struct bda_state_info *s;

  s = (struct bda_state_info *)malloc(sizeof *s);
  memset(s, 0, sizeof *s);
  assert(s != NULL);
  s->env = env;
  s->mode = JVM;
  s->transitions_in_stack = 0;
  bda_thread_context_init(s);
  return s;
}

void bda_state_free(struct bda_state_info *s)
{
    free((void *)s->thread_name);
    bda_thread_context_destroy(s);
    free(s);
}

struct bda_state_info *bda_get_state_info(JNIEnv *env)
{
  jvmtiError err;
  struct bda_state_info *s = NULL;

  if (bda_jvmti != NULL) {
      err = (*bda_jvmti)->GetThreadLocalStorage(bda_jvmti, NULL, (void**)&s);
      assert(err == JVMTI_ERROR_NONE);
  }

  return s;
}

int bda_get_current_transition_count()
{
  struct bda_state_info *s;

  assert(bda_jvmti != NULL);
  s=bda_get_state_info(NULL);
  assert(s != NULL);

  return s->transitions_in_stack;
}

void reset_transition_breakpoints()
{
  bda_j2c_call_breakpoint = 0;
  bda_j2c_return_breakpoint = 0;
  bda_c2j_call_breakpoint = 0;
  bda_c2j_return_breakpoint = 0;
}

static int is_transition_count_ok(int count)
{
  return ( bda_transition_count == 0) || (bda_transition_count == count);
}

void bda_state_j2c_call(struct bda_state_info *s, struct bda_native_method_frame *frame)
{
  s->mode = frame->is_user_method ? USR_NATIVE:SYS_NATIVE;
  s->transitions_in_stack++;
  s->j2c_counts++;

  if (bda_j2c_call_breakpoint && (bda_jvmti != NULL)
      && (s->mode == USR_NATIVE)
      && is_transition_count_ok(s->transitions_in_stack)) {
    struct bda_location loc;

    bda_init_location(&loc);
    loc.native_address = frame->native_method_address;
    bda_cbp(J2C_JNI_CALL, s, &loc);
    
    bda_release_location(&loc);
  }
}

void bda_state_j2c_return(struct bda_state_info *s, struct bda_native_method_frame *frame)
{
  if (bda_j2c_return_breakpoint && (bda_jvmti != NULL)
      && (s->mode == USR_NATIVE)
      && is_transition_count_ok(s->transitions_in_stack)) {
    struct bda_location loc;

    bda_init_location(&loc);
    bda_get_return_location(bda_jvmti, &loc);
    bda_cbp(J2C_JNI_RETURN, s, &loc);
    bda_release_location(&loc);
  }

  s->mode = JVM;
  s->transitions_in_stack--;
}

void bda_state_c2j_call(struct bda_state_info *s, struct bda_jni_function_frame *frame)
{
  assert(s != NULL && frame->caller_fp != NULL && frame->return_addr != NULL);
  s->c2j_counts++;

  /* push the recent c2j. */
  if (!frame->jdwp_context) {
    frame->prev = s->head_c2j;
    s->head_c2j = frame;
    s->transitions_in_stack++;
  }

  if (bda_c2j_call_breakpoint && bda_jvmti && !frame->jdwp_context
      && (frame->call_type != JNI_CALL_NOT_CLASSIFIED)
      && is_transition_count_ok(s->transitions_in_stack)) {
    struct bda_location loc;
        
    bda_init_location(&loc);
    bda_get_c2j_target(s, frame, &loc);
    bda_cbp(C2J_JNI_CALL, s, &loc);
    bda_release_location(&loc);
  }
  s->mode = JVM;
}

void bda_state_c2j_return(struct bda_state_info *s, struct bda_jni_function_frame *frame)
{
  assert (s != NULL && frame != NULL);
  assert (frame->jdwp_context || s->head_c2j == frame);

  if (bda_c2j_return_breakpoint && bda_jvmti && !frame->jdwp_context
      && (frame->call_type != JNI_CALL_NOT_CLASSIFIED)
      && is_transition_count_ok(s->transitions_in_stack)) {
    struct bda_location loc;

    bda_init_location(&loc);
    bda_cbp(C2J_JNI_RETURN, s, NULL);
    bda_release_location(&loc);
  }

  if (!frame->jdwp_context) {
    s->head_c2j = s->head_c2j->prev;
    s->transitions_in_stack--;
  }
}

int bda_state_get_transition_count(JNIEnv *env)
{
  struct bda_state_info *s = bda_get_state_info(env);
  if (s == NULL) {
      return -1;
  } else {
      return s->transitions_in_stack;
  }
}
