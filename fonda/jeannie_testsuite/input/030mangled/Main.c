#include <jni.h>
#include <stdio.h>
#include "mangledcasts.h"

struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 {
};

int JNICALL Java_Main_00024JavaEnvFor_1main_j2c(JNIEnv *env, jobject jEnv) {
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 cEnv;
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 *pcEnv = &cEnv;

  return printf("%d\n", (int) ({
    jclass cls = (*env)->GetObjectClass(env, jEnv);
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j", "(J)I");
    jint tmp;
    tmp = (*env)->CallNonvirtualIntMethod(env, jEnv, cls, mid, env2long(pcEnv));
    (*env)->DeleteLocalRef(env, cls);
    if ((*env)->ExceptionCheck(env) ||  ({
      jclass cls = (*env)->GetObjectClass(env, jEnv);
      jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt", "Z");
      jboolean tmp = (*env)->GetBooleanField(env, jEnv, fid);
      (*env)->DeleteLocalRef(env, cls);
      tmp;
    })) {
      return (int)0;
    }
    tmp;
  }));
  pcEnv = 0;
}
