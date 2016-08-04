#include <jni.h>
#include <stdio.h>
#include "mangledcasts.h"

struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 {
};

void JNICALL Java_Main_00024JavaEnvFor_1Main_1main_1_1_13Ljava_10002flang_10002fString_12_j2c(JNIEnv *env, jobject jEnv) {
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 cEnv;
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 *pcEnv = &cEnv;
  printf("C1\n"); fflush(stdout);
  {
    jclass cls = (*env)->GetObjectClass(env, jEnv);
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j", "(J)V");
    (*env)->CallNonvirtualVoidMethod(env, jEnv, cls, mid, env2long(pcEnv));
    if ((*env)->ExceptionCheck(env)
	|| ({
	  jclass cls = (*env)->GetObjectClass(env, jEnv);
	  jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt", "Z");
	  (*env)->GetBooleanField(env, jEnv, fid);      
	}))
      return;
  }
  printf("C2\n"); fflush(stdout);
}
