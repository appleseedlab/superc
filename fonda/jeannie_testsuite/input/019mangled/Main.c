#include <jni.h>
#include <stdlib.h>
#include "mangledcasts.h"

struct CEnvFor_Main_sum {
  int _i, _n;
  jint* _ca, _s;
  jintArray _caJavaArray;
  jboolean _caIsCopy;
};

void JNICALL Java_Main_00024JavaEnvFor_1Main_1sum_j2c(JNIEnv *env, jobject jEnv) {
  struct CEnvFor_Main_sum cEnv;
  struct CEnvFor_Main_sum* pcEnv = &cEnv;
  pcEnv->_n = ({
    jclass cls = (*env)->GetObjectClass(env, jEnv);
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j1", "(J)I");
    (*env)->CallNonvirtualIntMethod(env, jEnv, cls, mid, env2long(pcEnv));
  });
  pcEnv->_s = 0;
  /* `withArray(ca = ja) { */
  {
    pcEnv->_caJavaArray = ({
      jclass cls = (*env)->GetObjectClass(env, jEnv);
      jmethodID mid = (*env)->GetMethodID(env, cls, "c2j2", "(J)[I");
      (*env)->CallNonvirtualObjectMethod(env, jEnv, cls, mid, env2long(pcEnv));
    });
    pcEnv->_ca = (*env)->GetPrimitiveArrayCritical(env, pcEnv->_caJavaArray, 
                                                   &pcEnv->_caIsCopy);
    /* for (i=0; i<n; i++) s += ca[i]; */
    for (pcEnv->_i=0; pcEnv->_i<pcEnv->_n; pcEnv->_i++)
      pcEnv->_s += pcEnv->_ca[pcEnv->_i];
    /*   `abort ca; */
    (*env)->ReleasePrimitiveArrayCritical(env, pcEnv->_caJavaArray, 
                                          pcEnv->_ca, JNI_ABORT);
  }
  /* } */
  {
    jclass cls = (*env)->GetObjectClass(env, jEnv);
    jfieldID fid = (*env)->GetFieldID(env, cls, "_result", "I");
    (*env)->SetIntField(env, jEnv, fid, pcEnv->_s);
  }
}
