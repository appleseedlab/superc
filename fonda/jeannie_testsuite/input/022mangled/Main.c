#include <jni.h>
#include <stdio.h>
#include "mangledcasts.h"

struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 {
  jstring _bsJavaArray;
  jboolean _bsIsCopy;
  char *_bs;
  jint _bsReleaseMode;
};

void JNICALL Java_Main_00024JavaEnvFor_1Main_1main_1_1_13Ljava_10002flang_10002fString_12_j2c(JNIEnv *env, jobject jEnv) {
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 cEnv;
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 *pcEnv = &cEnv;
  {
      pcEnv->_bsJavaArray =  ({
        jclass cls = (*env)->GetObjectClass(env, jEnv);
        jmethodID mid = (*env)->GetMethodID(env, cls, "c2j", "(J)Ljava/lang/String;");
        jstring tmp;

        tmp = (*env)->CallNonvirtualObjectMethod(env, jEnv, cls, mid, env2long(pcEnv));
        if ((*env)->ExceptionCheck(env) ||  ({
          jclass cls = (*env)->GetObjectClass(env, jEnv);
          jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt", "Z");

          (*env)->GetBooleanField(env, jEnv, fid);
        })) {
          return;
        }
        tmp;
      });

      pcEnv->_bs = (char*)(*env)->GetStringUTFChars(env, pcEnv->_bsJavaArray, &pcEnv->_bsIsCopy);
      {
        printf("%*s\n", (int) ({
          jclass cls = (*env)->GetObjectClass(env, jEnv);
          jmethodID mid = (*env)->GetMethodID(env, cls, "c2j1", "(J)I");
          jint tmp;

          tmp = (*env)->CallNonvirtualIntMethod(env, jEnv, cls, mid, env2long(pcEnv));
          if ((*env)->ExceptionCheck(env) ||  ({
            jclass cls = (*env)->GetObjectClass(env, jEnv);
            jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt", "Z");

            (*env)->GetBooleanField(env, jEnv, fid);
          })) {
            {
              pcEnv->_bsReleaseMode = 2;
              goto release_bs;
            }
          }
          tmp;
        }), pcEnv->_bs);

      }
    release_bs:
      (*env)->ReleaseStringUTFChars(env, pcEnv->_bsJavaArray, pcEnv->_bs);
      if ((*env)->ExceptionCheck(env) ||  ({
        jclass cls = (*env)->GetObjectClass(env, jEnv);
        jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt", "Z");

        (*env)->GetBooleanField(env, jEnv, fid);
      })) {
        return;
      }
    }
}
