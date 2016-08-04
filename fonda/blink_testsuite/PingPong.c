












#include <jni.h>
#include <stdio.h>
JNIEXPORT jint JNICALL Java_PingPong_cPong(
  JNIEnv *env, jclass cls, jint i
) {
  printf("cPong: %d\n", i);
  if ( i > 0) {
    jmethodID mid = (*env)->GetStaticMethodID(env, cls, "jPing", "(I)I");
      (*env)->CallStaticIntMethod(env, cls, mid, i-1);
  }
  return i;
}
