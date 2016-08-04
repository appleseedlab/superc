#include <jni.h>
#include "mangledcasts.h"

struct CEnvFor_Main_replace___3CCC {
  unsigned short _old;
  unsigned short _new;
  long _len;
  struct _jobject *_sJavaArray;
  int _i;
  jchar *_s;
  long _sReleaseAbrupt;
};

void JNICALL Java_Main_00024JavaEnvFor_1replace_j2c(JNIEnv *env, jobject jEnv) {
  struct CEnvFor_Main_replace___3CCC cEnv;
  struct CEnvFor_Main_replace___3CCC *pcEnv = &cEnv;
  {

    pcEnv->_old = (jchar) ({
      jclass cls = (*env)->GetObjectClass(env, jEnv);
      jmethodID mid = (*env)->GetMethodID(env, cls, "c2j", "(J)C");
      jchar tmp;

      tmp = (*env)->CallNonvirtualCharMethod(env, jEnv, cls, mid, env2long(pcEnv));
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

    pcEnv->_new = (jchar) ({
      jclass cls = (*env)->GetObjectClass(env, jEnv);
      jmethodID mid = (*env)->GetMethodID(env, cls, "c2j1", "(J)C");
      jchar tmp;

      tmp = (*env)->CallNonvirtualCharMethod(env, jEnv, cls, mid, env2long(pcEnv));
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

    pcEnv->_len = (jint) ({
      jclass cls = (*env)->GetObjectClass(env, jEnv);
      jmethodID mid = (*env)->GetMethodID(env, cls, "c2j2", "(J)I");
      jint tmp;

      tmp = (*env)->CallNonvirtualIntMethod(env, jEnv, cls, mid, env2long(pcEnv));
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
 {
      pcEnv->_sJavaArray =  ({
        jclass cls = (*env)->GetObjectClass(env, jEnv);
        jmethodID mid = (*env)->GetMethodID(env, cls, "c2j3", "(J)[C");
        jcharArray tmp;

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

      pcEnv->_sReleaseAbrupt = 0;
      {

        jint length = (*env)->GetArrayLength(env, pcEnv->_sJavaArray);
        jchar ca[length];

        pcEnv->_s = ca;
        (*env)->GetCharArrayRegion(env, pcEnv->_sJavaArray, 0, length, pcEnv->_s);
        {
          {
            pcEnv->_i = (int)0;
            for (; pcEnv->_i < pcEnv->_len; pcEnv->_i++) {
              if (pcEnv->_old == pcEnv->_s[pcEnv->_i]) {
                pcEnv->_s[pcEnv->_i] = pcEnv->_new;
                {

                  jclass cls = (*env)->GetObjectClass(env, jEnv);
                  jfieldID fidResult = (*env)->GetFieldID(env, cls, "_returnResult", "I");

                  (*env)->SetIntField(env, jEnv, fidResult, (jint)pcEnv->_i);

                  jfieldID fidAbrupt = (*env)->GetFieldID(env, cls, "_returnAbrupt", "Z");

                  (*env)->SetBooleanField(env, jEnv, fidAbrupt, 1);
                  goto release_s;
                }
              }
            }
          } {
            pcEnv->_sReleaseAbrupt = 2;
            goto release_s;
          }
        }
        goto release_s;
      release_s:
        if (2 != pcEnv->_sReleaseAbrupt)
          (*env)->SetCharArrayRegion(env, pcEnv->_sJavaArray, 0, length, pcEnv->_s);
      }
      if ((*env)->ExceptionCheck(env) ||  ({
        jclass cls = (*env)->GetObjectClass(env, jEnv);
        jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt", "Z");
        jboolean tmp = (*env)->GetBooleanField(env, jEnv, fid);

        (*env)->DeleteLocalRef(env, cls);
        tmp;
      })) {
        return;
      }
    } {

      jclass cls = (*env)->GetObjectClass(env, jEnv);
      jfieldID fidResult = (*env)->GetFieldID(env, cls, "_returnResult", "I");

      (*env)->SetIntField(env, jEnv, fidResult, (jint)-1);

      jfieldID fidAbrupt = (*env)->GetFieldID(env, cls, "_returnAbrupt", "Z");

      (*env)->SetBooleanField(env, jEnv, fidAbrupt, 1);
      return;
    }
  }
  pcEnv = 0;
}
