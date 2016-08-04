









#include <jni.h>

JNIEXPORT jstring JNICALL Java_BadNullArgument_foo(JNIEnv *env, jclass cls)
{
    return (*env)->NewStringUTF(env, NULL);
}
