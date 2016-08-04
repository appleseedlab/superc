#include <jni.h>
#include <stdio.h>

JNIEXPORT void JNICALL Java_GlobalRefDangling_foo (JNIEnv * env, jclass cls) {
    jclass gref = (*env)->NewGlobalRef(env, cls);
    (*env)->DeleteGlobalRef(env, gref);
    (*env)->GetStaticMethodID(env, gref, "foo", "()V");
}
