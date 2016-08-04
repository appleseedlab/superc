#include <jni.h>

jobject badGlob;

void JNICALL Java_Main_00024JavaEnvFor_1setGlob_j2c(JNIEnv *env, jobject jEnv) {
  jclass cls = (*env)->GetObjectClass(env, jEnv);
  if ( ({
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j", "()Z");
    (*env)->CallNonvirtualBooleanMethod(env, jEnv, cls, mid);
  }))
    ({
      jmethodID mid = (*env)->GetMethodID(env, cls, "c2j1", "()Ljava/io/PrintWriter;");
      (*env)->CallNonvirtualObjectMethod(env, jEnv, cls, mid);
    });
  else
    badGlob = ({
      jmethodID mid = (*env)->GetMethodID(env, cls, "c2j2", "()Ljava/io/PrintWriter;");
      (*env)->CallNonvirtualObjectMethod(env, jEnv, cls, mid);
    });
}

void JNICALL Java_Main_00024JavaEnvFor_1getGlob_j2c1(JNIEnv *env, jobject jEnv) {
  jclass cls = (*env)->GetObjectClass(env, jEnv);
  if ( ({
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j3", "()Z");
    (*env)->CallNonvirtualBooleanMethod(env, jEnv, cls, mid);
  })) {
    jfieldID fidResult = (*env)->GetFieldID(env, cls, "_returnResult", "Ljava/io/PrintWriter;");
    (*env)->SetObjectField(env, jEnv, fidResult, ({
      jmethodID mid = (*env)->GetMethodID(env, cls, "c2j4", "()Ljava/io/PrintWriter;");
      (*env)->CallNonvirtualObjectMethod(env, jEnv, cls, mid);
    }));
  } else {
    jfieldID fidResult = (*env)->GetFieldID(env, cls, "_returnResult", "Ljava/io/PrintWriter;");
    (*env)->SetObjectField(env, jEnv, fidResult, badGlob);
  }
}

void JNICALL Java_Main_00024JavaEnvFor_1useGlob_j2c2(JNIEnv *env, jobject jEnv) {
  jclass cls = (*env)->GetObjectClass(env, jEnv);
  jmethodID mid = (*env)->GetMethodID(env, cls, "c2j5", "()V");
  (*env)->CallNonvirtualVoidMethod(env, jEnv, cls, mid);
}
