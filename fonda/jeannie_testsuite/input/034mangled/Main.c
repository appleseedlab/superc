#include <jni.h>

jint _stringUTFLength(JNIEnv* env, jstring str, jint start, jint len) {
  jint result = len;
  const jchar* chars = (*env)->GetStringCritical(env, str, 0x0);
  jint i;
  for (i=0; i<len; i++) {
    const jchar c = chars[start + i];
    if (c == (jchar)0x0000) result++;
    else if (c >= (jchar)0x0080) {
      result++;
      if (c >= (jchar)0x0800) result++;
    }
  }
  (*env)->ReleaseStringCritical(env, str, chars);
  return result;
}

void JNICALL Java_Main_00024JavaEnvFor_1substringUtf8LengthNative_j2c(JNIEnv *env, jobject jEnv) {
  jclass cls = (*env)->GetObjectClass(env, jEnv);
  jfieldID fidResult = (*env)->GetFieldID(env, cls, "_returnResult", "I");
  (*env)->SetIntField(env, jEnv, fidResult, _stringUTFLength(env, ({
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j", "(I)Ljava/lang/String;");
    (*env)->CallNonvirtualObjectMethod(env, jEnv, cls, mid, 0);
  }), ({
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j1", "(I)I");
    (*env)->CallNonvirtualIntMethod(env, jEnv, cls, mid, 0);
  }), ({
    jmethodID mid = (*env)->GetMethodID(env, cls, "c2j2", "(I)I");
    (*env)->CallNonvirtualIntMethod(env, jEnv, cls, mid, 0);
  })));
}
