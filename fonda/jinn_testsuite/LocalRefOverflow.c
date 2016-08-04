#include <jni.h>
#include <stdio.h>


JNIEXPORT void JNICALL Java_LocalRefOverflow_foo (
    JNIEnv * env, jclass clazz, jobject vector) {
    char cstr[128];
    int i;
    jclass cls_vector = (*env)->GetObjectClass(env, vector); /* 1 local reference.*/
    jmethodID mid = (*env)->GetMethodID(env, cls_vector, "addElement", "(Ljava/lang/Object;)V");
    if (mid == NULL) {return;}
    /* Create 16 local references. */
    for (i=0; i < 16; i++) {
        jstring jstr;
        sprintf(cstr, "limit %d", i);
        jstr = (*env)->NewStringUTF(env, cstr);
        if (jstr == NULL) {return;}
        (*env)->CallVoidMethod(env, vector, mid, jstr);
        if ((*env)->ExceptionCheck(env)) {
            return;
        }
    }
}
