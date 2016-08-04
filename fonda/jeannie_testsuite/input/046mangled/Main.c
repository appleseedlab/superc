#include <jni.h>
#include "mangledcasts.h"

struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 {
  FILE *_out;
  struct _jobject *_caJavaArray;
  long _i;
  jint *_ca;
  long _caReleaseAbrupt;
};

void JNICALL Java_Main_00024JavaEnvFor_1main_j2c(JNIEnv *env, jobject jEnv, const jlong cEnv) {
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 *pcEnv = long2env(cEnv, CEnvFor_Main_main___3Ljava_0002flang_0002fString_2);
  {

    pcEnv->_out =  ({
      FILE *tmp;

      tmp = fopen("tmp/046mangled/written_file.txt", "w");
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
      pcEnv->_caJavaArray =  ({
        jclass cls = (*env)->GetObjectClass(env, jEnv);
        jmethodID mid = (*env)->GetMethodID(env, cls, "c2j", "(J)[I");
        jintArray tmp;

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

        jint length = (*env)->GetArrayLength(env, pcEnv->_caJavaArray);
        jint ca[length];

        pcEnv->_ca = ca;
        (*env)->GetIntArrayRegion(env, pcEnv->_caJavaArray, 0, length, pcEnv->_ca);
        {
          {
            pcEnv->_i = (jint)0;
            for (; pcEnv->_i < 4; pcEnv->_i++) {
              if (pcEnv->_ca[pcEnv->_i] == 0) {
                jclass cls = (*env)->GetObjectClass(env, jEnv);
                jmethodID mid = (*env)->GetMethodID(env, cls, "c2j1", "(J)V");

                (*env)->CallNonvirtualVoidMethod(env, jEnv, cls, mid, env2long(pcEnv));
                (*env)->DeleteLocalRef(env, cls);
                {
                  if ((*env)->ExceptionCheck(env))
                    pcEnv->_caReleaseAbrupt = 2;
                  if (pcEnv->_caReleaseAbrupt ||  ({
                    jclass cls = (*env)->GetObjectClass(env, jEnv);
                    jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt", "Z");
                    jboolean tmp = (*env)->GetBooleanField(env, jEnv, fid);

                    (*env)->DeleteLocalRef(env, cls);
                    tmp;
                  })) {
                    goto release_ca;
                  }
                }
              }
              pcEnv->_ca[pcEnv->_i] = 10 / pcEnv->_ca[pcEnv->_i];
               ({
                int tmp;

                tmp = fprintf(pcEnv->_out, "ca[%d] == %d\n", (int)pcEnv->_i, (int)pcEnv->_ca[pcEnv->_i]);
                {
                  if ((*env)->ExceptionCheck(env))
                    pcEnv->_caReleaseAbrupt = 2;
                  if (pcEnv->_caReleaseAbrupt ||  ({
                    jclass cls = (*env)->GetObjectClass(env, jEnv);
                    jfieldID fid = (*env)->GetFieldID(env, cls, "_returnAbrupt", "Z");
                    jboolean tmp = (*env)->GetBooleanField(env, jEnv, fid);

                    (*env)->DeleteLocalRef(env, cls);
                    tmp;
                  })) {
                    goto release_ca;
                  }
                }
                tmp;
              });

            }
          }
        }
        goto release_ca;
      release_ca:
        if (2 != pcEnv->_caReleaseAbrupt)
          (*env)->SetIntArrayRegion(env, pcEnv->_caJavaArray, 0, length, pcEnv->_ca);
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

void JNICALL Java_Main_00024JavaEnvFor_1main_j2c1(JNIEnv *env, jobject jEnv, const jlong cEnv) {
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 *pcEnv = long2env(cEnv, CEnvFor_Main_main___3Ljava_0002flang_0002fString_2);
  {

     ({
      int tmp;

      tmp = fprintf(pcEnv->_out, "division by zero\n");
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

void JNICALL Java_Main_00024JavaEnvFor_1main_j2c2(JNIEnv *env, jobject jEnv, const jlong cEnv) {
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 *pcEnv = long2env(cEnv, CEnvFor_Main_main___3Ljava_0002flang_0002fString_2);
  {

     ({
      int tmp;

      tmp = fclose(pcEnv->_out);
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

void JNICALL Java_Main_00024JavaEnvFor_1main_j2c3(JNIEnv *env, jobject jEnv) {
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 cEnv;
  struct CEnvFor_Main_main___3Ljava_0002flang_0002fString_2 *pcEnv = &cEnv;
  {
    {
      jclass cls = (*env)->GetObjectClass(env, jEnv);
      jmethodID mid = (*env)->GetMethodID(env, cls, "c2j2", "(J)V");

      (*env)->CallNonvirtualVoidMethod(env, jEnv, cls, mid, env2long(pcEnv));
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
    }
  }
  pcEnv = 0;
}
