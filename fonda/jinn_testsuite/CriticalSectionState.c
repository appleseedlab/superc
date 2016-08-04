#include <jni.h>
#include <stdio.h>

JNIEXPORT void JNICALL Java_CriticalSectionState_cfoo(
    JNIEnv * env, jclass cls, jstring jstr) {
  jboolean isCopy;
  jmethodID mid;
  mid = (*env)->GetStaticMethodID(env, cls, "jbar", "()V");
  const jchar * cstr = (*env)->GetStringCritical(env, jstr, &isCopy);
  (*env)->CallStaticVoidMethod(env, cls, mid); /*A bad JNI call*/
  (*env)->ReleaseStringCritical(env, jstr, cstr);
}
