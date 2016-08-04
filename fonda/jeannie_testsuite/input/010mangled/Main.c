#include <jni.h>
jint JNICALL Java_Main_00024JavaEnvFor_1main_j2c(JNIEnv *env, jobject obj) {
  return (jint)(1 + ({
    jclass cls = (*env)->GetObjectClass(env, obj);
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j", "()I");
    jint result = (*env)->CallNonvirtualIntMethod(env, obj, cls, mid);
    result;
  }));
}
