#include <jni.h>
int printf(const char*, ...);
void JNICALL Java_Main_foo(JNIEnv *env, jclass clazz) {
  jclass clazzMath = (*env)->FindClass(env, "Ljava/lang/Math;");
  jmethodID mid = (*env)->GetStaticMethodID(env, clazzMath, "max", "(II)I");
  int y = (*env)->CallStaticIntMethod(env, clazzMath, mid, 123, 456);
  printf("return value: %d\n", y);
}
