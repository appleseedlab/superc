#include <jni.h>

JNIEXPORT jstring JNICALL Java_MonitorLeak_foo(JNIEnv *env, jclass cls)
{
    (*env)->MonitorEnter(env, cls);
}
