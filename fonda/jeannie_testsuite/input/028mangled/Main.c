#include <jni.h>
#include <stdio.h>
#include "mangledcasts.h"

static JavaVM* javaVM = NULL;

struct CEnvForF {
  char* _s;
  int _x;
};

void f(char* s, int x) {
  JNIEnv* env;
  (*javaVM)->AttachCurrentThread(javaVM, (void**)&env, NULL);
  struct CEnvForF cEnv;
  struct CEnvForF* pcEnv = &cEnv;
  pcEnv->_s = s;
  pcEnv->_x = x;
  jobject jEnv = ({
      jclass cls = (*env)->FindClass(env, "JavaEnvForF");
      jmethodID mid = (*env)->GetMethodID(env, cls, "<init>", "()V");
      (*env)->NewObject(env, cls, mid);
    });
  printf("f(\"%s\", %d) 1\n", s, x); fflush(stdout);
  {
    jclass cls = (*env)->GetObjectClass(env, jEnv);
    jmethodID mid = (*env)->GetMethodID(env, cls, "callMainG", "(J)V");
    (*env)->CallNonvirtualVoidMethod(env, jEnv, cls, mid, env2long(pcEnv));
  }
  printf("f(\"%s\", %d) 2\n", s, x); fflush(stdout);
}

jint JNICALL Java_JavaEnvForF_retrieveX(JNIEnv* env, jclass clazz, jlong cEnv) {
  struct CEnvForF* pcEnv = long2env(cEnv, CEnvForF);
  return (jint)pcEnv->_x;
}

void JNICALL Java_Main_callF(JNIEnv *env, jclass clazz) {
  f("hello", 123);
}

void JNICALL Java_Main_onLoad(JNIEnv* env, jclass clazz) {
  (*env)->GetJavaVM(env, &javaVM);
}
