#include <jni.h>
int printf(const char*, ...);
void JNICALL Java_Main_sayHi(JNIEnv *env, jclass clazz) {
  printf("Hello world!\n");
}
