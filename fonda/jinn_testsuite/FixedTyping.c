#include <stdio.h>
#include <jni.h>

JNIEXPORT void JNICALL Java_FixedTyping_foo(
    JNIEnv *env, jobject obj) {
  jfieldID fid = (*env)->GetFieldID(env, obj, "number", "I");
  jint field = (*env)->GetIntField(env, obj, fid);
  printf("field is %d\n", field);
}
