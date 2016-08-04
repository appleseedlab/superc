#include <jni.h>
#include "mangledcasts.h"

struct CEnvFor_Main_culprit {
  int _i;
};

void JNICALL Java_Main_00024JavaEnvFor_1culprit_j2c(JNIEnv *env, jobject jEnv) {
  struct CEnvFor_Main_culprit cEnv;
  struct CEnvFor_Main_culprit *pcEnv = &cEnv;
  for (pcEnv->_i = 0; pcEnv->_i < 100000; pcEnv->_i++) {
    jclass cls = (*env)->GetObjectClass(env, jEnv);
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j", "(J)V");
    (*env)->CallNonvirtualVoidMethod(env, jEnv, cls, mid, env2long(pcEnv));
    (*env)->DeleteLocalRef(env, cls); /* remove to victimize */
    if ((*env)->ExceptionCheck(env) ||  ({
      jclass cls = (*env)->GetObjectClass(env, jEnv);
      jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt", "Z");
      jboolean tmp = (*env)->GetBooleanField(env, jEnv, fid);
      (*env)->DeleteLocalRef(env, cls); /* remove to victimize */
      tmp;
    })) {
      return;
    }
  }
}

struct CEnvFor_Main_victim {
};

void JNICALL Java_Main_00024JavaEnvFor_1victim_j2c1(JNIEnv *env, jobject jEnv) {
  struct CEnvFor_Main_victim cEnv;
  struct CEnvFor_Main_victim *pcEnv = &cEnv;
  jclass cls = (*env)->GetObjectClass(env, jEnv);
  jmethodID mid = (*env)->GetMethodID(env, cls, "c2j1", "(J)V");

  (*env)->CallNonvirtualVoidMethod(env, jEnv, cls, mid, env2long(pcEnv));
  if ((*env)->ExceptionCheck(env) ||  ({
    jclass cls = (*env)->GetObjectClass(env, jEnv);
    jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt1", "Z");

    (*env)->GetBooleanField(env, jEnv, fid);
  })) {
    return;
  }
}
