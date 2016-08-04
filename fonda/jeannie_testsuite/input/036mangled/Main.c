#include <jni.h>
#include "mangledcasts.h"

struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 {
  long _caReleaseAbrupt;
  struct _jobject *_caJavaArray;
  struct _jobject *_t;
  jobject *_ca;
};

void JNICALL Java_Main_00024JavaEnvFor_1main_j2c(JNIEnv *env, jobject jEnv) {
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 cEnv;
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 *pcEnv = &cEnv;
  {
    {

      pcEnv->_caJavaArray =  ({
        jclass cls = (*env)->GetObjectClass(env, jEnv);
        jmethodID mid = (*env)->GetMethodID(env, cls, "c2j", "(J)[Ljava/lang/String;");
        jobjectArray tmp;

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

      pcEnv->_caReleaseAbrupt = 0;
      {

        jsize i;
        jint length = (*env)->GetArrayLength(env, pcEnv->_caJavaArray);
        jobject ca[length];

        pcEnv->_ca = ca;
        for (i = 0; i < length; i++)
          ca[i] = (*env)->GetObjectArrayElement(env, pcEnv->_caJavaArray, i);
        {
          pcEnv->_t = (jobject)pcEnv->_ca[0];
          pcEnv->_ca[0] = pcEnv->_ca[2];
          pcEnv->_ca[2] = pcEnv->_t;
        }
        goto release_ca;
      release_ca:
        if (2 != pcEnv->_caReleaseAbrupt)
          for (i = 0; i < length; i++) {
            (*env)->SetObjectArrayElement(env, pcEnv->_caJavaArray, i, ca[i]);
            if ((*env)->ExceptionCheck(env))
              break;
          }
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
    }
  }
  pcEnv = 0;
}
