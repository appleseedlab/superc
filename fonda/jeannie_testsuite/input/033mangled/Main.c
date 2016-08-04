#include <jni.h>

void JNICALL Java_Main_00024JavaEnvFor_1utf16LengthNative_j2c(JNIEnv *env, jobject jEnv) {
  jclass cls = (*env)->GetObjectClass(env, jEnv);
  jfieldID fidResult = (*env)->GetFieldID(env, cls, "_returnResult", "I");
  (*env)->SetIntField(env, jEnv, fidResult, ({
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j", "(I)I");
    (*env)->CallNonvirtualIntMethod(env, jEnv, cls, mid, 0x0);
  }));
}

void JNICALL Java_Main_00024JavaEnvFor_1utf8LengthNative_j2c1(JNIEnv *env, jobject jEnv) {
  jclass cls = (*env)->GetObjectClass(env, jEnv);
  jfieldID fidResult = (*env)->GetFieldID(env, cls, "_returnResult1", "I");
  (*env)->SetIntField(env, jEnv, fidResult, (*env)->GetStringUTFLength(env, ({
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j1", "(I)Ljava/lang/String;");
    (*env)->CallNonvirtualObjectMethod(env, jEnv, cls, mid, 0x0);
  })));
}
