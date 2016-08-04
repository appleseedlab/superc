#include <jni.h>
#include <stdio.h>

static jclass globalRef;

JNIEXPORT void JNICALL Java_WeakGlobalRefLeak_foo (
    JNIEnv * env, jclass cls) {
    globalRef = (*env)->NewWeakGlobalRef(env, cls);
}
