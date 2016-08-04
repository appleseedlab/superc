#include <jni.h>
#include <stdio.h>
#include "mangledcasts.h"

struct CEnvFor_main {
  int _c1;
  int _c2;
};

void JNICALL Java_Main_00024JavaEnvFor_1main_j2c2(JNIEnv *env, jobject obj) {
  struct CEnvFor_main cEnv;
  struct CEnvFor_main* pcEnv = &cEnv;
  pcEnv->_c2 = 0;
  ({
    jclass cls = (*env)->GetObjectClass(env,obj);
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j1", "(J)V");
    (*env)->CallNonvirtualVoidMethod(env, obj, cls, mid, env2long(pcEnv));
  });
  printf("c2: expected 2, got %d\n", pcEnv->_c2);
}

void JNICALL Java_Main_00024JavaEnvFor_1main_j2c1(JNIEnv *env, jobject obj, jlong cEnv){
  struct CEnvFor_main* pcEnv = long2env(cEnv, CEnvFor_main);
  pcEnv->_c1 = 0;
  ({
    jclass cls = (*env)->GetObjectClass(env,obj);
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j0", "(J)V");
    (*env)->CallNonvirtualVoidMethod(env, obj, cls, mid, env2long(pcEnv));
  });
  pcEnv->_c2++;
  printf("c1: expected 1, got %d\n", pcEnv->_c1);
}

void JNICALL Java_Main_00024JavaEnvFor_1main_j2c0(JNIEnv *env, jobject obj, jlong cEnv){
  struct CEnvFor_main* pcEnv = long2env(cEnv, CEnvFor_main);
  pcEnv->_c2++;
  pcEnv->_c1++;
}
