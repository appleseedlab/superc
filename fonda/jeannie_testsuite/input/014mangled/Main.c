#include <stdio.h>
#include <jni.h>
#include "mangledcasts.h"

struct CEnvFor_Main_f___3I {
  jint *_ca;
  jintArray _caJavaArray;
  jboolean _caIsCopy;
  jint _caReleaseMode;
  int _i;
};

void JNICALL Java_Main_00024JavaEnvFor_1Main_1f_1_1_13I_j2c(JNIEnv *env, jobject jEnv){
  struct CEnvFor_Main_f___3I cEnv;
  struct CEnvFor_Main_f___3I *pcEnv = &cEnv;
  pcEnv->_caJavaArray = ({
    jclass cls = (*env)->GetObjectClass(env, jEnv);
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j", "(J)[I");
    jintArray tmp = (*env)->CallNonvirtualObjectMethod(
      env, jEnv, cls, mid, env2long(pcEnv));
    if ((*env)->ExceptionCheck(env)) return;
    tmp;
  });
  pcEnv->_caReleaseMode = 0;
  pcEnv->_ca = (*env)->GetIntArrayElements(
    env, pcEnv->_caJavaArray, &pcEnv->_caIsCopy);
  for (pcEnv->_i = 0; pcEnv->_i < 3; pcEnv->_i++) {
    if (pcEnv->_ca[pcEnv->_i] == 4) {
      jclass cls = (*env)->GetObjectClass(env, jEnv);
      jmethodID mid = (*env)->GetMethodID(env, cls, "c2j1", "(J)V");
      (*env)->CallNonvirtualVoidMethod(env, jEnv, cls, mid, env2long(pcEnv));
      if ((*env)->ExceptionCheck(env)) {
        pcEnv->_caReleaseMode = 0;
        goto release_ca;
      }
    }
    printf("p0 (%d %d)\n", pcEnv->_i, (int)pcEnv->_ca[pcEnv->_i]);
    fflush(stdout);
  }
  printf("p1\n");
  fflush(stdout);
  pcEnv->_caReleaseMode = 0;
  goto release_ca;
 release_ca:
  (*env)->ReleaseIntArrayElements(
    env, pcEnv->_caJavaArray, pcEnv->_ca, pcEnv->_caReleaseMode);
  if ((*env)->ExceptionCheck(env)) return;
  printf("p2\n");
  fflush(stdout);
}
