#include <jni.h>
#include "mangledcasts.h"

struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 {
  struct _jobject *_intOrFloat;
  struct _jobject *_f;
  struct _jobject *_i;
};

jobject JNICALL Java_Main_00024JavaEnvFor_1main_j2c(JNIEnv *env, jobject jEnv, const jlong cEnv) {
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 *pcEnv = long2env(cEnv, CEnvFor_Main_main___3Ljava_0002flang_0002fString_2);
  return pcEnv->_intOrFloat;
  pcEnv = 0;
}

void JNICALL Java_Main_00024JavaEnvFor_1main_j2c1(JNIEnv *env, jobject jEnv) {
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 cEnv;
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 *pcEnv = &cEnv;
  if ( ({
    jclass cls = (*env)->GetObjectClass(env, jEnv);
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j", "(J)Z");
    (*env)->CallNonvirtualBooleanMethod(env, jEnv, cls, mid, env2long(pcEnv));
  }) ) {
    pcEnv->_f = (jobject) ({
      jclass cls = (*env)->GetObjectClass(env, jEnv);
      jmethodID mid = (*env)->GetMethodID(env, cls, "c2j1", "(J)Ljava/lang/Float;");
      (*env)->CallNonvirtualObjectMethod(env, jEnv, cls, mid, env2long(pcEnv));
    });
    pcEnv->_intOrFloat = pcEnv->_f;
  } else {
    pcEnv->_i = (jobject) ({
      jclass cls = (*env)->GetObjectClass(env, jEnv);
      jmethodID mid = (*env)->GetMethodID(env, cls, "c2j2", "(J)Ljava/lang/Integer;");
      (*env)->CallNonvirtualObjectMethod(env, jEnv, cls, mid, env2long(pcEnv));
    });
    pcEnv->_intOrFloat = pcEnv->_i;
  }
  {
    jclass cls = (*env)->GetObjectClass(env, jEnv);
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j3", "(J)V");
    (*env)->CallNonvirtualVoidMethod(env, jEnv, cls, mid, env2long(pcEnv));
  }
  pcEnv = 0;
}
