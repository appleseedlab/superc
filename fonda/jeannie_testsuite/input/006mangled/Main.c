#include <jni.h>
#include "foo.h"

void JNICALL Java_Main_sayHi(JNIEnv *env, jclass clazz) {
  bar();
}
