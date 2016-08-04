#include <jni.h>
#include <stdio.h>

JNIEXPORT void JNICALL Java_WeakGlobalRefDangling_foo (JNIEnv * env, jclass cls) {
    jclass gref = (*env)->NewWeakGlobalRef(env, cls);
    (*env)->DeleteWeakGlobalRef(env, gref);
    (*env)->GetStaticMethodID(env, gref, "foo", "()V");
}
