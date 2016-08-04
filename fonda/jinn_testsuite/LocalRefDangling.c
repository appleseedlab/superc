#include <jni.h>
#include <stdio.h>

static jclass localRefCls;

JNIEXPORT void JNICALL Java_LocalRefDangling_initNative (JNIEnv * env, jclass cls) {
  localRefCls = (*env)->FindClass(env, "LocalRefDangling");
}

JNIEXPORT void JNICALL Java_LocalRefDangling_foo (JNIEnv * env, jobject obj) {
  (*env)->GetMethodID(env, localRefCls, "bar", "()V");
}
