#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include "mangledcasts.h"

struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 {
  char *_bs;
};

void JNICALL Java_Main_00024JavaEnvFor_1Main_1main_1_1_13Ljava_10002flang_10002fString_12_j2c(JNIEnv *env, jobject jEnv) {
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 cEnv;
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 *pcEnv = &cEnv;
  pcEnv->_bs = (char*)malloc(4);
  pcEnv->_bs[3] = '\0';
  (*env)->GetStringUTFRegion(env, ({
    jclass cls = (*env)->GetObjectClass(env, jEnv);
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j", "(J)Ljava/lang/String;");
    jstring tmp =
      (*env)->CallNonvirtualObjectMethod(env, jEnv, cls, mid, env2long(pcEnv));
    if ((*env)->ExceptionCheck(env) ||  ({
      jclass cls = (*env)->GetObjectClass(env, jEnv);
      jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt", "Z");
      (*env)->GetBooleanField(env, jEnv, fid);
    }))
      return;
    tmp;
  }), 0, 3, pcEnv->_bs + 0);
  if ((*env)->ExceptionCheck(env) || ({
    jclass cls = (*env)->GetObjectClass(env, jEnv);
    jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt", "Z");
    (*env)->GetBooleanField(env, jEnv, fid);
  }))
    return;
  printf("%s\n", pcEnv->_bs);
  free(pcEnv->_bs);
}
