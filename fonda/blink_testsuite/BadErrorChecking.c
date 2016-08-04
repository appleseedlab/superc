#include <jni.h>

JNIEXPORT void Java_BadErrorChecking_call (JNIEnv *env, jobject obj) {
  jclass cls = (*env)->GetObjectClass(env, obj);
  jmethodID mid = (*env)->GetMethodID(env, cls, "foo", "()V");
  (*env)->CallVoidMethod(env, obj, mid); // exception from Java
  mid = (*env)->GetMethodID(env, cls, "bar", "()V"); // 1. Violated exception state
  (*env)->CallVoidMethod(env, obj, mid);  // 2. Violated exception state
}
