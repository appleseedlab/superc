#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <jni.h>
#include "mangledcasts.h"

jint _stringUTFLength(JNIEnv *env, jstring str, jint start, jint len) {
  jint result = len;
  const jchar *chars = (*env)->GetStringCritical(env, str, 0x0);
  jint i;

  for (i = 0; i < len; i++) {
    const jchar c = chars[start + i];

    if (c == (jchar)0x0000)
      result++;
    else if (c >= (jchar)0x0080) {
      result++;
      if (c >= (jchar)0x0800)
        result++;
    }
  }
  (*env)->ReleaseStringCritical(env, str, chars);
  return result;
}

void JNICALL Java_StdIO_00024JavaEnvFor_1stdOut_j2c(JNIEnv *env, jobject jEnv) {
  jclass cls = (*env)->GetObjectClass(env, jEnv);
  jfieldID fidResult = (*env)->GetFieldID(env, cls, "_returnResult", "J");
  (*env)->SetLongField(env, jEnv, fidResult, ptr2long(stdout));
  jfieldID fidAbrupt = (*env)->GetFieldID(env, cls, "_returnAbrupt", "Z");
  (*env)->SetBooleanField(env, jEnv, fidAbrupt, 1);
}

struct CEnvFor_StdIO_fputs {
  long _len;
  jbyte *_cs;
  int _result;
};

jstring JNICALL Java_StdIO_00024JavaEnvFor_1fputs_j2c1(JNIEnv *env, jobject jEnv, const jlong cEnv) {
  struct CEnvFor_StdIO_fputs *pcEnv = long2env(cEnv, CEnvFor_StdIO_fputs);

  return  ({
    jstring tmp = (*env)->NewStringUTF(env, strerror(errno));

    if ((*env)->ExceptionCheck(env) ||  ({
      jclass cls = (*env)->GetObjectClass(env, jEnv);
      jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt1", "Z");
      jboolean tmp = (*env)->GetBooleanField(env, jEnv, fid);

      (*env)->DeleteLocalRef(env, cls);
      tmp;
    })) {
      return (jstring)0;
    }
    tmp;
  });

  pcEnv = 0;
}

void JNICALL Java_StdIO_00024JavaEnvFor_1fputs_j2c2(JNIEnv *env, jobject jEnv) {
  struct CEnvFor_StdIO_fputs cEnv;
  struct CEnvFor_StdIO_fputs *pcEnv = &cEnv;
  {

    pcEnv->_len = (jint)(*env)->GetStringUTFLength(env,  ({
      jclass cls = (*env)->GetObjectClass(env, jEnv);
      jmethodID mid = (*env)->GetMethodID(env, cls, "c2j", "(J)Ljava/lang/String;");
      jstring tmp;

      tmp = (*env)->CallNonvirtualObjectMethod(env, jEnv, cls, mid, env2long(pcEnv));
      (*env)->DeleteLocalRef(env, cls);
      if ((*env)->ExceptionCheck(env) ||  ({
        jclass cls = (*env)->GetObjectClass(env, jEnv);
        jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt1", "Z");
        jboolean tmp = (*env)->GetBooleanField(env, jEnv, fid);

        (*env)->DeleteLocalRef(env, cls);
        tmp;
      })) {
        return;
      }
      tmp;
    }));


    jbyte cs[1 + pcEnv->_len];

    pcEnv->_cs = cs;
     ({
      jstring javaArray =  ({
        jclass cls = (*env)->GetObjectClass(env, jEnv);
        jmethodID mid = (*env)->GetMethodID(env, cls, "c2j1", "(J)Ljava/lang/String;");
        jstring tmp;

        tmp = (*env)->CallNonvirtualObjectMethod(env, jEnv, cls, mid, env2long(pcEnv));
        (*env)->DeleteLocalRef(env, cls);
        if ((*env)->ExceptionCheck(env) ||  ({
          jclass cls = (*env)->GetObjectClass(env, jEnv);
          jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt1", "Z");
          jboolean tmp = (*env)->GetBooleanField(env, jEnv, fid);

          (*env)->DeleteLocalRef(env, cls);
          tmp;
        })) {
          return;
        }
        tmp;
      });
      jint start = 0, length =  ({
        jclass cls = (*env)->GetObjectClass(env, jEnv);
        jmethodID mid = (*env)->GetMethodID(env, cls, "c2j2", "(J)I");
        jint tmp;

        tmp = (*env)->CallNonvirtualIntMethod(env, jEnv, cls, mid, env2long(pcEnv));
        (*env)->DeleteLocalRef(env, cls);
        if ((*env)->ExceptionCheck(env) ||  ({
          jclass cls = (*env)->GetObjectClass(env, jEnv);
          jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt1", "Z");
          jboolean tmp = (*env)->GetBooleanField(env, jEnv, fid);

          (*env)->DeleteLocalRef(env, cls);
          tmp;
        })) {
          return;
        }
        tmp;
      });

      (*env)->GetStringUTFRegion(env, javaArray, start, length, (char *)(pcEnv->_cs + 0));
      if ((*env)->ExceptionCheck(env) ||  ({
        jclass cls = (*env)->GetObjectClass(env, jEnv);
        jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt1", "Z");
        jboolean tmp = (*env)->GetBooleanField(env, jEnv, fid);

        (*env)->DeleteLocalRef(env, cls);
        tmp;
      })) {
        return;
      }
      _stringUTFLength(env, javaArray, start, length);
    });

    pcEnv->_cs[pcEnv->_len] = '\0';
    pcEnv->_result =  ({
      int tmp;

      tmp = fputs((char *)pcEnv->_cs, (FILE *) long2ptr( ({
        jclass cls = (*env)->GetObjectClass(env, jEnv);
        jmethodID mid = (*env)->GetMethodID(env, cls, "c2j3", "(J)J");
        jlong tmp;

        tmp = (*env)->CallNonvirtualLongMethod(env, jEnv, cls, mid, env2long(pcEnv));
        (*env)->DeleteLocalRef(env, cls);
        if ((*env)->ExceptionCheck(env) ||  ({
          jclass cls = (*env)->GetObjectClass(env, jEnv);
          jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt1", "Z");
          jboolean tmp = (*env)->GetBooleanField(env, jEnv, fid);

          (*env)->DeleteLocalRef(env, cls);
          tmp;
        })) {
          return;
        }
        tmp;
      }) ));

      if ((*env)->ExceptionCheck(env) ||  ({
        jclass cls = (*env)->GetObjectClass(env, jEnv);
        jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt1", "Z");
        jboolean tmp = (*env)->GetBooleanField(env, jEnv, fid);

        (*env)->DeleteLocalRef(env, cls);
        tmp;
      })) {
        return;
      }
      tmp;
    });

    if (-1 == pcEnv->_result) {
      jclass cls = (*env)->GetObjectClass(env, jEnv);
      jmethodID mid = (*env)->GetMethodID(env, cls, "c2j4", "(J)V");

      (*env)->CallNonvirtualVoidMethod(env, jEnv, cls, mid, env2long(pcEnv));
      (*env)->DeleteLocalRef(env, cls);
      if ((*env)->ExceptionCheck(env) ||  ({
        jclass cls = (*env)->GetObjectClass(env, jEnv);
        jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt1", "Z");
        jboolean tmp = (*env)->GetBooleanField(env, jEnv, fid);

        (*env)->DeleteLocalRef(env, cls);
        tmp;
      })) {
        return;
      }
    }
  }
  pcEnv = 0;
}

struct CEnvFor_StdIO_fflush {
  int _result1;
};

jstring JNICALL Java_StdIO_00024JavaEnvFor_1fflush_j2c3(JNIEnv *env, jobject jEnv, const jlong cEnv) {
  struct CEnvFor_StdIO_fflush *pcEnv = long2env(cEnv, CEnvFor_StdIO_fflush);

  return  ({
    jstring tmp = (*env)->NewStringUTF(env, strerror(errno));

    if ((*env)->ExceptionCheck(env) ||  ({
      jclass cls = (*env)->GetObjectClass(env, jEnv);
      jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt2", "Z");
      jboolean tmp = (*env)->GetBooleanField(env, jEnv, fid);

      (*env)->DeleteLocalRef(env, cls);
      tmp;
    })) {
      return (jstring)0;
    }
    tmp;
  });

  pcEnv = 0;
}

void JNICALL Java_StdIO_00024JavaEnvFor_1fflush_j2c4(JNIEnv *env, jobject jEnv) {
  struct CEnvFor_StdIO_fflush cEnv;
  struct CEnvFor_StdIO_fflush *pcEnv = &cEnv;
  {

    pcEnv->_result1 = (int) ({
      int tmp;

      tmp = fflush((FILE *) long2ptr( ({
        jclass cls = (*env)->GetObjectClass(env, jEnv);
        jmethodID mid = (*env)->GetMethodID(env, cls, "c2j5", "(J)J");
        jlong tmp;

        tmp = (*env)->CallNonvirtualLongMethod(env, jEnv, cls, mid, env2long(pcEnv));
        (*env)->DeleteLocalRef(env, cls);
        if ((*env)->ExceptionCheck(env) ||  ({
          jclass cls = (*env)->GetObjectClass(env, jEnv);
          jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt2", "Z");
          jboolean tmp = (*env)->GetBooleanField(env, jEnv, fid);

          (*env)->DeleteLocalRef(env, cls);
          tmp;
        })) {
          return;
        }
        tmp;
      }) ));

      if ((*env)->ExceptionCheck(env) ||  ({
        jclass cls = (*env)->GetObjectClass(env, jEnv);
        jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt2", "Z");
        jboolean tmp = (*env)->GetBooleanField(env, jEnv, fid);

        (*env)->DeleteLocalRef(env, cls);
        tmp;
      })) {
        return;
      }
      tmp;
    });

    if (-1 == pcEnv->_result1) {
      jclass cls = (*env)->GetObjectClass(env, jEnv);
      jmethodID mid = (*env)->GetMethodID(env, cls, "c2j6", "(J)V");

      (*env)->CallNonvirtualVoidMethod(env, jEnv, cls, mid, env2long(pcEnv));
      (*env)->DeleteLocalRef(env, cls);
      if ((*env)->ExceptionCheck(env) ||  ({
        jclass cls = (*env)->GetObjectClass(env, jEnv);
        jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt2", "Z");
        jboolean tmp = (*env)->GetBooleanField(env, jEnv, fid);

        (*env)->DeleteLocalRef(env, cls);
        tmp;
      })) {
        return;
      }
    }
  }
  pcEnv = 0;
}
