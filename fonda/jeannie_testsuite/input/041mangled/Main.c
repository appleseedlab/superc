#include <stdio.h>
#include <jni.h>

int JNICALL Java_Main_00024JavaEnvFor_1main_j2c(JNIEnv *env, jobject jEnv) {
  return printf("Hello, world!\n");
}
