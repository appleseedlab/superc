#include <jni.h>

JNIEXPORT jstring JNICALL Java_Nullness_foo(JNIEnv *env, jclass cls)
{
    return (*env)->NewStringUTF(env, NULL);
}
