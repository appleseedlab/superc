#ifndef _STATE_H_
#define _STATE_H_

#include <jni.h>
#include <jvmti.h>

enum bda_mode {
    JVM, 
    SYS_NATIVE, 
    USR_NATIVE,
};

enum bda_c2j_call_type {
  JNI_CALL_NOT_CLASSIFIED,
  JNI_CALL_INSTANCE,
  JNI_CALL_NONVIRTUAL,
  JNI_CALL_STATIC,
};

/* per-thread JNI state info. */
struct bda_state_info {
  JNIEnv *env;
  const char *thread_name;
    char *msgbuf;
  
  enum bda_mode mode;
  struct bda_jni_function_frame *head_c2j;
  int transitions_in_stack;
  
  struct bda_local_frame *local_frame_top;
  int critical;
  struct htable *open_criticals;
 
  int j2c_counts;
  int c2j_counts;
};

struct bda_jni_function_frame {
  void *caller_fp;
  void *return_addr;
  int jdwp_context;
  struct bda_jni_function_frame *prev;

  /* For Call...Method only. */
  enum bda_c2j_call_type call_type;
  jclass class;
  jobject object;
  jmethodID mid;
};

struct bda_native_method_frame {
  JNIEnv *env;
  jmethodID methodID;
  void *native_method_address;
  int is_user_method;
};

#if defined(__GNUC__)
extern __thread struct bda_state_info *bda_tls_state;
#elif defined(_WIN32)
extern __declspec(thread) struct bda_state_info *bda_tls_state;
#else
#error "no support for this platform"
#endif

/* notify JNI state change. */
extern struct bda_state_info *bda_state_allocate(JNIEnv *env);
extern void bda_state_free(struct bda_state_info *s);
extern struct bda_state_info *bda_tls_state_get();

extern void bda_state_j2c_call(
    struct bda_state_info *s, 
    struct bda_native_method_frame *native_frame);
extern void bda_state_j2c_return(
    struct bda_state_info *s, 
    struct bda_native_method_frame *native_frame);
extern void bda_state_c2j_call(
    struct bda_state_info *s, 
    struct bda_jni_function_frame *jni_function_frame);
extern void bda_state_c2j_return(
    struct bda_state_info *s, 
struct bda_jni_function_frame *jni_function_frame);

/* query JNI state. */
extern int bda_state_get_transition_count(JNIEnv *env);
extern struct bda_state_info *bda_get_state_info(JNIEnv *env);
extern int bda_get_current_transition_count();

/* breakpoints */
extern void bda_reset_transition_breakpoints();

extern void bda_c2j_proxy_install(jvmtiEnv *jvmti);
extern void bda_j2c_proxy_add(jvmtiEnv *jvmti, JNIEnv *env, jmethodID method, 
                              void *address, void **new_address_ptr);

extern void bda_j2c_proxy_deferred_methods_reregister(jvmtiEnv *jvmti, JNIEnv *env);
extern void bda_j2c_proxy_add_deferred(jmethodID method, void *address);

#endif /** _STATE_H_ */
