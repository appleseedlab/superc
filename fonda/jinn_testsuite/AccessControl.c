#include <stdio.h>
#include <jni.h>

JNIEXPORT void JNICALL Java_AccessControl_mutateString(
    JNIEnv *env, jclass cls, jstring s)
{
  jclass str_class = (*env)->GetObjectClass(env, s);
  jfieldID fid =(*env)->GetFieldID(env, str_class, "value", "[C");
  (*env)->SetObjectField(env, s, fid, NULL);
}
