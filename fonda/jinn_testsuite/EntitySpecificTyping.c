#include <stdio.h>
#include <jni.h>

JNIEXPORT void JNICALL Java_EntitySpecificTyping_foo(JNIEnv *env, jobject obj) {
    jfieldID fid = (*env)->GetFieldID(
        env, (*env)->GetObjectClass(env, obj), "obj", "Ljava/lang/Object;");
    (*env)->SetIntField(env, obj, fid, 0x60000000);
}
