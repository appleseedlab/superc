#include <jni.h>
#include <stdio.h>

static JavaVM* javaVM = NULL;

void f() {
  JNIEnv* env;
  (*javaVM)->AttachCurrentThread(javaVM, (void**)&env, NULL);
  jobject jEnv = ({
      jclass cls = (*env)->FindClass(env, "JavaEnvForF");
      jmethodID mid = (*env)->GetMethodID(env, cls, "<init>", "()V");
      (*env)->NewObject(env, cls, mid);
    });
  printf("f 1\n"); fflush(stdout);
  {
    jclass cls = (*env)->GetObjectClass(env, jEnv);
    jmethodID mid = (*env)->GetMethodID(env, cls, "callMainG", "()V");
    (*env)->CallNonvirtualVoidMethod(env, jEnv, cls, mid);
  }
  printf("f 2\n"); fflush(stdout);
}

void JNICALL Java_Main_callF(JNIEnv *env, jclass clazz) {
  f();
}

void JNICALL Java_Main_onLoad(JNIEnv* env, jclass clazz) {
  (*env)->GetJavaVM(env, &javaVM);
}
