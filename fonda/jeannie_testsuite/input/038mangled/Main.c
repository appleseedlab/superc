#include <jni.h>
#include "mangledcasts.h"

struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 {
  struct _jobject *_s;
  struct _jobject *_o;
};

void JNICALL Java_Main_00024JavaEnvFor_1main_j2c(JNIEnv *env, jobject jEnv) {
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 cEnv;
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 *pcEnv = &cEnv;
  pcEnv->_s = (jstring) ({
    jclass cls = (*env)->GetObjectClass(env, jEnv);
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j", "(J)Ljava/lang/String;");
    (*env)->CallNonvirtualObjectMethod(env, jEnv, cls, mid, env2long(pcEnv));
  });
  pcEnv->_o = (jobject) ({
    jclass cls = (*env)->GetObjectClass(env, jEnv);
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j1", "(J)Ljava/lang/String;");
    (*env)->CallNonvirtualObjectMethod(env, jEnv, cls, mid, env2long(pcEnv));
  });
  pcEnv->_o = pcEnv->_s;
  pcEnv->_s = ({
    jclass cls = (*env)->GetObjectClass(env, jEnv);
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j2", "(J)Ljava/lang/String;");
    (*env)->CallNonvirtualObjectMethod(env, jEnv, cls, mid, env2long(pcEnv));
  });
}
