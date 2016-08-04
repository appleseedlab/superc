#include <jni.h>
#include <stdio.h>
void JNICALL Java_Main_sayHi(JNIEnv *env, jclass clazz) {
  printf("Hello world!\n");
}
