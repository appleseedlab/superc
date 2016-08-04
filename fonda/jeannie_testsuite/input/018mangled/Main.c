#include <stdio.h>
#include <jni.h>

#define REPEAT 100 * 1000

void JNICALL Java_Main_emptyCBlockInJava_1j2c(JNIEnv *env, jclass cls) {
}

void JNICALL Java_Main_emptyJavaBlockInC_1j2c(JNIEnv *env, jclass cls) {
  long long n = REPEAT;
  long long i;
  for (i=0; i<n; i++) {
    jmethodID mid =
      (*env)->GetStaticMethodID(env, cls, "emptyJavaBlockInC_c2j", "()V");
    (*env)->CallStaticVoidMethod(env, cls, mid);
    if ((*env)->ExceptionCheck(env))
      return;
  }
}

jint JNICALL Java_Main_constantCExpressionInJava_1j2c(JNIEnv *env, jclass cls) {
  return 1;
}

void JNICALL Java_Main_constantJavaExpressionInC_1j2c(JNIEnv *env, jclass cls) {
  long long n = REPEAT;
  long long s = 0;
  long long i;
  for (i=0; i<n; i++)
    s += ({
      jmethodID mid = (*env)->GetStaticMethodID(
        env, cls, "constantJavaExpressionInC_c2j", "()I");
      jint tmp = (*env)->CallStaticIntMethod(env, cls, mid);
      if ((*env)->ExceptionCheck(env))
        return;
      tmp;
    });
  if (n != s)
    printf("error\n");
}

void JNICALL Java_Main_arrayReadAccess_1j2c(JNIEnv *env, jclass cls) {
  long long n = REPEAT;
  long long s = 0;
  long long i;
  jintArray ja;
  jint* ca;
  jboolean isCopy;
  ja = ({
    jmethodID mid = (*env)->GetStaticMethodID(
      env, cls, "arrayReadAccess_c2j", "()[I");
    jintArray tmp = (*env)->CallStaticObjectMethod(env, cls, mid);
    if ((*env)->ExceptionCheck(env))
      return;
    tmp;
  });
  ca = (*env)->GetIntArrayElements(env, ja, &isCopy);
  for (i=0; i<n; i++)
    s += ca[i % 1000];
  (*env)->ReleaseIntArrayElements(env, ja, ca, 0);
  if ((*env)->ExceptionCheck(env))
    return;
  if (n != s) printf("error\n");
}

void JNICALL Java_Main_arrayWriteAccess_1j2c(JNIEnv *env, jclass cls, jintArray ja) {
  long long n = REPEAT;
  jboolean isCopy;
  long long i; 
  jint* ca = (*env)->GetIntArrayElements(env, ja, &isCopy);
  for (i=0; i<n; i++)
    ca[i % 1000] = 1;
  (*env)->ReleaseIntArrayElements(env, ja, ca, 0);
}

void JNICALL Java_Main_exceptionJavaInCInJava_1j2c(JNIEnv *env, jclass cls) {
  jmethodID mid = (*env)->GetStaticMethodID(
    env, cls, "exceptionJavaInCInJava_c2j", "()V");
  (*env)->CallStaticVoidMethod(env, cls, mid);
  if ((*env)->ExceptionCheck(env))
    return;
  printf("should not be printed\n");
}
