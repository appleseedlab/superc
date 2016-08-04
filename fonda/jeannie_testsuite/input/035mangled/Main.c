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

struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 {
  jbyte *_b;
  jchar *_j;
  int _lb1;
  int _lc;
};

void JNICALL Java_Main_00024JavaEnvFor_1main_j2c(JNIEnv *env, jobject jEnv) {
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 cEnv;
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 *pcEnv = &cEnv;
  {
    jbyte b[100];

    pcEnv->_b = b;

    jchar j[100];

    pcEnv->_j = j;
    pcEnv->_lb1 = (int) ({
      jstring javaArray =  ({
        jclass cls = (*env)->GetObjectClass(env, jEnv);
        jmethodID mid = (*env)->GetMethodID(env, cls, "c2j", "(J)Ljava/lang/String;");
        jstring tmp;

        tmp = (*env)->CallNonvirtualObjectMethod(env, jEnv, cls, mid, env2long(pcEnv));
        (*env)->DeleteLocalRef(env, cls);
        if ((*env)->ExceptionCheck(env) ||  ({
          jclass cls = (*env)->GetObjectClass(env, jEnv);
          jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt", "Z");
          jboolean tmp = (*env)->GetBooleanField(env, jEnv, fid);

          (*env)->DeleteLocalRef(env, cls);
          tmp;
        })) {
          return;
        }
        tmp;
      });
      jint start = 3, length = 8;

      (*env)->GetStringUTFRegion(env, javaArray, start, length, (char *)(pcEnv->_b + 0));
      if ((*env)->ExceptionCheck(env) ||  ({
        jclass cls = (*env)->GetObjectClass(env, jEnv);
        jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt", "Z");
        jboolean tmp = (*env)->GetBooleanField(env, jEnv, fid);

        (*env)->DeleteLocalRef(env, cls);
        tmp;
      })) {
        return;
      }
      _stringUTFLength(env, javaArray, start, length);
    });

    pcEnv->_lc = (int) ({
      jint length;

      (*env)->GetStringRegion(env,  ({
        jclass cls = (*env)->GetObjectClass(env, jEnv);
        jmethodID mid = (*env)->GetMethodID(env, cls, "c2j1", "(J)Ljava/lang/String;");
        jstring tmp;

        tmp = (*env)->CallNonvirtualObjectMethod(env, jEnv, cls, mid, env2long(pcEnv));
        (*env)->DeleteLocalRef(env, cls);
        if ((*env)->ExceptionCheck(env) ||  ({
          jclass cls = (*env)->GetObjectClass(env, jEnv);
          jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt", "Z");
          jboolean tmp = (*env)->GetBooleanField(env, jEnv, fid);

          (*env)->DeleteLocalRef(env, cls);
          tmp;
        })) {
          return;
        }
        tmp;
      }), 3, length = 8, pcEnv->_j + 0);

      if ((*env)->ExceptionCheck(env) ||  ({
        jclass cls = (*env)->GetObjectClass(env, jEnv);
        jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt", "Z");
        jboolean tmp = (*env)->GetBooleanField(env, jEnv, fid);

        (*env)->DeleteLocalRef(env, cls);
        tmp;
      })) {
        return;
      }
      length;
    });

     ({
      int tmp;
      pcEnv->_b[pcEnv->_lb1] = '\0';
      tmp = printf("|%s| == %d bytes == %d chars\n", pcEnv->_b, pcEnv->_lb1, pcEnv->_lc);
      if ((*env)->ExceptionCheck(env) ||  ({
        jclass cls = (*env)->GetObjectClass(env, jEnv);
        jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt", "Z");
        jboolean tmp = (*env)->GetBooleanField(env, jEnv, fid);

        (*env)->DeleteLocalRef(env, cls);
        tmp;
      })) {
        return;
      }
      tmp;
    });

  }
  pcEnv = 0;
}
