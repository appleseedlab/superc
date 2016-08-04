#include <jni.h>
#include "mangledcasts.h"

struct CEnvFor_Main_replace___3CCC {
  int _i;
};

int JNICALL Java_Main_00024JavaEnvFor_1replace_j2c(JNIEnv *env, jobject jEnv, const jlong cEnv) {
  struct CEnvFor_Main_replace___3CCC *pcEnv = long2env(cEnv, CEnvFor_Main_replace___3CCC);

  return pcEnv->_i;
  pcEnv = 0;
}

int JNICALL Java_Main_00024JavaEnvFor_1replace_j2c1(JNIEnv *env, jobject jEnv, const jlong cEnv) {
  struct CEnvFor_Main_replace___3CCC *pcEnv = long2env(cEnv, CEnvFor_Main_replace___3CCC);

  return pcEnv->_i;
  pcEnv = 0;
}

void JNICALL Java_Main_00024JavaEnvFor_1replace_j2c2(JNIEnv *env, jobject jEnv) {
  struct CEnvFor_Main_replace___3CCC cEnv;
  struct CEnvFor_Main_replace___3CCC *pcEnv = &cEnv;
  {
    {

      pcEnv->_i = (int)0;
      for (; pcEnv->_i <  ({
        jclass cls = (*env)->GetObjectClass(env, jEnv);
        jmethodID mid = (*env)->GetMethodID(env, cls, "c2j", "(J)I");
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
      }); pcEnv->_i++) {
        if ( ({
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
        }) ==  ({
          jclass cls = (*env)->GetObjectClass(env, jEnv);
          jmethodID mid = (*env)->GetMethodID(env, cls, "c2j2", "(J)C");
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
        })) {
           ({
            jclass cls = (*env)->GetObjectClass(env, jEnv);
            jmethodID mid = (*env)->GetMethodID(env, cls, "c2j3", "(J)C");
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
 {

            jclass cls = (*env)->GetObjectClass(env, jEnv);
            jfieldID fidResult = (*env)->GetFieldID(env, cls, "_returnResult", "I");

            (*env)->SetIntField(env, jEnv, fidResult, (jint)pcEnv->_i);

            jfieldID fidAbrupt = (*env)->GetFieldID(env, cls, "_returnAbrupt", "Z");

            (*env)->SetBooleanField(env, jEnv, fidAbrupt, 1);
            return;
          }
        }
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
