#include <stdio.h>
#include <jni.h>
#include "mangledcasts.h"

struct CEnvFor_Main_f__I {
  jint _y;
};

void JNICALL Java_Main_00024JavaEnvFor_1Main_1f_1_1I_m1(
  JNIEnv *env, jobject jEnv
) {
  struct CEnvFor_Main_f__I cEnv;
  struct CEnvFor_Main_f__I *pcEnv = &cEnv;
  pcEnv->_y = 0;
  {
    jclass cls = (*env)->GetObjectClass(env, jEnv);
    jmethodID mid = (*env)->GetMethodID(env, cls, "m2", "(J)V");
    (*env)->CallNonvirtualVoidMethod(env, jEnv, cls, mid, env2long(pcEnv));
  }
  printf("%d\n", (int)pcEnv->_y);
}

jint JNICALL Java_Main_00024JavaEnvFor_1Main_1f_1_1I_m3(
  JNIEnv *env, jobject jEnv, const jlong cEnv
) {
  struct CEnvFor_Main_f__I *pcEnv = long2env(cEnv, CEnvFor_Main_f__I);
  return pcEnv->_y = 1 + ({
    jclass cls = (*env)->GetObjectClass(env, jEnv);
    jmethodID mid = (*env)->GetMethodID(env, cls, "m4", "(J)I");
    (*env)->CallNonvirtualIntMethod(env, jEnv, cls, mid, env2long(pcEnv));
  });
}
