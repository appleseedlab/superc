#include <jni.h>
#include <math.h>

void JNICALL Java_Math_00024JavaEnvFor_1pow_j2c(JNIEnv *env, jobject jEnv) {
  jdouble x = ({
      jclass cls = (*env)->GetObjectClass(env, jEnv);
      jmethodID mid = (*env)->GetMethodID(env, cls, "getX", "()D");
      (*env)->CallNonvirtualDoubleMethod(env, jEnv, cls, mid);
    });
  jdouble y = ({
      jclass cls = (*env)->GetObjectClass(env, jEnv);
      jmethodID mid = (*env)->GetMethodID(env, cls, "getY", "()D");
      (*env)->CallNonvirtualDoubleMethod(env, jEnv, cls, mid);
    });
  jclass cls = (*env)->GetObjectClass(env, jEnv);
  jdouble result = (jdouble) pow(x, y);
  jfieldID fidResult = (*env)->GetFieldID(env, cls, "_returnResult", "D");
  (*env)->SetDoubleField(env, jEnv, fidResult, result);
}
