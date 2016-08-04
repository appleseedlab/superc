#ifndef _AGENT_MAIN_H_
#define _AGENT_MAIN_H_

extern JavaVM *bda_jvm;
extern jvmtiEnv *bda_jvmti;
extern jniNativeInterface *bda_orig_jni_funcs;

extern int bda_is_in_jdwp_region(void *address);

#endif /* _AGENT_MAIN_H_ */
