#include <jni.h>
#include <stdio.h>

JNIEXPORT void JNICALL Java_VMResourceLeak_foo(
  JNIEnv * env, jclass cls, jstring jstr) {
  const char* cstr = (*env)->GetStringUTFChars(env, jstr, NULL);
  if (cstr == NULL) {return;}
}
