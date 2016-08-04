#include <jni.h>
#include <stdio.h>

static jclass globalRef;

JNIEXPORT void JNICALL Java_GlobalRefLeak_foo (
    JNIEnv * env, jclass cls) {
    globalRef = (*env)->NewGlobalRef(env, cls);
}
