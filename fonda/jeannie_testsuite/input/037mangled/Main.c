#include <jni.h>

void JNICALL Java_Main_00024JavaEnvFor_1main_j2c(JNIEnv *env, jobject jEnv) {
  printf("%d\n", (int) ({
    jclass cls = (*env)->GetObjectClass(env, jEnv);
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j", "()I");
    (*env)->CallNonvirtualIntMethod(env, jEnv, cls, mid);
  }));
  fflush(stdout);
}
