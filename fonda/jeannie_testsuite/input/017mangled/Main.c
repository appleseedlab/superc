#include <jni.h>
#include <stdio.h>
#include "mangledcasts.h"

struct CEnvFor_Main_f___3I {
  jint _n;
  jintArray _caJavaArray;
  jint _caReleaseMode;
  jboolean _caIsCopy;
  jint *_ca;
  jint _i;
};

#define abruptTerminationCheck(env, fieldName) \
  (*env)->ExceptionCheck(env) || ({ \
    jclass cls = (*env)->GetObjectClass(env, jEnv); \
    jfieldID fid = (*env)->GetFieldID(env, cls, fieldName, "Z"); \
    (*env)->GetBooleanField(env, jEnv, fid); \
  })

#define abruptReturnPrepare(env, result, resultFieldName, abruptFieldName) \
  jclass cls = (*env)->GetObjectClass(env, jEnv); \
  jfieldID fidResult = (*env)->GetFieldID(env, cls, resultFieldName, "I"); \
  (*env)->SetIntField(env, jEnv, fidResult, result); \
  jfieldID fidAbrupt = (*env)->GetFieldID(env, cls, abruptFieldName, "Z"); \
  (*env)->SetBooleanField(env, jEnv, fidAbrupt, 1);


void JNICALL Java_Main_00024JavaEnvFor_1Main_1f_1_1_13I_j2c(JNIEnv *env, jobject jEnv) {
  struct CEnvFor_Main_f___3I cEnv;
  struct CEnvFor_Main_f___3I *pcEnv = &cEnv;
  pcEnv->_n = ({
    jclass cls = (*env)->GetObjectClass(env, jEnv);
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j", "(J)I");
    jint tmp = (*env)->CallNonvirtualIntMethod(env, jEnv, cls, mid, env2long(pcEnv));
    if (abruptTerminationCheck(env, "_returnAbrupt"))
      return;
    tmp;
  });
  pcEnv->_caJavaArray = ({
    jclass cls = (*env)->GetObjectClass(env, jEnv);
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j1", "(J)[I");
    jintArray tmp = (*env)->CallNonvirtualObjectMethod(env, jEnv, cls, mid, env2long(pcEnv));
    if (abruptTerminationCheck(env, "_returnAbrupt"))
      return;
    tmp;
  });
  pcEnv->_caReleaseMode = 0;
  pcEnv->_ca = (*env)->GetIntArrayElements(env, pcEnv->_caJavaArray, &pcEnv->_caIsCopy);
  for (pcEnv->_i = 0; pcEnv->_i < pcEnv->_n; pcEnv->_i++)
    if (0 == pcEnv->_ca[pcEnv->_i]) {
      abruptReturnPrepare(env, pcEnv->_i, "_returnResult", "_returnAbrupt");
      goto release_ca;
    }
  printf("not found\n");
 release_ca:
  (*env)->ReleaseIntArrayElements(env, pcEnv->_caJavaArray, pcEnv->_ca, pcEnv->_caReleaseMode);
  if (abruptTerminationCheck(env, "_returnAbrupt"))
    return;
  {
    abruptReturnPrepare(env, -1, "_returnResult", "_returnAbrupt");
    return;
  }
}
