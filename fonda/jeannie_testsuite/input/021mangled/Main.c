#include <jni.h>
#include <stdlib.h>
#include "mangledcasts.h"

struct CEnvFor_Main_foo {
  int _i;
  jint _ca[4];
  jintArray _caJavaArray;
};

void JNICALL Java_Main_00024JavaEnvFor_1Main_1foo_j2c(JNIEnv *env, jobject jEnv) {
  struct CEnvFor_Main_foo cEnv;
  struct CEnvFor_Main_foo* pcEnv = &cEnv;
  /* `withArray(ca = ja [2 ... 6]) { */
  {
    pcEnv->_caJavaArray = ({
      jclass cls = (*env)->GetObjectClass(env, jEnv);
      jmethodID mid = (*env)->GetMethodID(env, cls, "c2j", "(J)[I");
      (*env)->CallNonvirtualObjectMethod(env, jEnv, cls, mid, env2long(pcEnv));
    });
    (*env)->GetIntArrayRegion(env, pcEnv->_caJavaArray, 2, 4, pcEnv->_ca);
    /* for (i=0; i<n; i++) s += ca[i]; */
    for (pcEnv->_i=0; pcEnv->_i<4; pcEnv->_i++)
      pcEnv->_ca[pcEnv->_i]++;
  }
  /* } */
  (*env)->SetIntArrayRegion(env, pcEnv->_caJavaArray, 2, 4, pcEnv->_ca);
}
