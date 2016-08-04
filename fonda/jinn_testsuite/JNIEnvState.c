















#include <stdio.h>
#include <jni.h>

static JNIEnv* mainThreadEnv;

JNIEXPORT void JNICALL Java_JNIEnvState_workInMainThread(JNIEnv *env, jobject obj)
{
  mainThreadEnv = env;
}

JNIEXPORT void JNICALL Java_JNIEnvState_workInMyThread(JNIEnv *env, jobject obj)
{
  jclass cls = (*env)->GetObjectClass(mainThreadEnv, obj);
}
