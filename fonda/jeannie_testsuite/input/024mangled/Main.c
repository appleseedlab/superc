#include <jni.h>
#include "mangledcasts.h"

int printf(const char*, ...);

struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 {
  jstring _csJavaArray;
  jboolean _csIsCopy;
  jchar *_cs;
};

void JNICALL Java_Main_00024JavaEnvFor_1Main_1main_1_1_13Ljava_10002flang_10002fString_12_j2c(JNIEnv *env, jobject jEnv) {
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 cEnv;
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 *pcEnv = &cEnv;
  pcEnv->_csJavaArray =  ({
    jclass cls = (*env)->GetObjectClass(env, jEnv);
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j", "(J)Ljava/lang/String;");
    jstring tmp;

    tmp = (*env)->CallNonvirtualObjectMethod(env, jEnv, cls, mid, env2long(pcEnv));
    if ((*env)->ExceptionCheck(env) ||  ({
      jclass cls = (*env)->GetObjectClass(env, jEnv);
      jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt", "Z");

      (*env)->GetBooleanField(env, jEnv, fid);
    })) {
      return;
    }
    tmp;
  });

  pcEnv->_cs = (jchar*) (*env)->GetStringCritical(env, pcEnv->_csJavaArray, &pcEnv->_csIsCopy);
  printf("%c-%c-%c\n", pcEnv->_cs[0], pcEnv->_cs[1], pcEnv->_cs[2]);
  (*env)->ReleaseStringCritical(env, pcEnv->_csJavaArray, pcEnv->_cs);
  if ((*env)->ExceptionCheck(env) ||  ({
    jclass cls = (*env)->GetObjectClass(env, jEnv);
    jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt", "Z");

    (*env)->GetBooleanField(env, jEnv, fid);
  })) {
    return;
  }
}
