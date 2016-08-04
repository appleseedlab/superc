















#include <jni.h>
#include <stdlib.h>
#include <math.h>

JNIEXPORT void JNICALL Java_CompoundData_parse (
  JNIEnv *env, jclass cls, jint size, 
  jdoubleArray doubles, jobject strings)
{
  int i;
  /* parse the Java strings to the C doubles. */
  jdouble* results = malloc( sizeof(jdouble) * size);
  for(i = 0; i < size;i++) {
    /* get string. */
    jclass jvector = (*env)->FindClass(env, "java/util/Vector");
    jmethodID mid_vget = (*env)->GetMethodID(env, jvector, "get", "(I)Ljava/lang/Object;");
    jstring jstr = (jstring)(*env)->CallObjectMethod(env, strings, mid_vget, i);
    /* keep the result. */
    const char* cstr = (*env)->GetStringUTFChars(env, jstr, 0);
    results[i] = atof(cstr);
    (*env)->ReleaseStringUTFChars(env, jstr, cstr); 
  }
  (*env)->SetDoubleArrayRegion(env, doubles, 0, size, results);
  free(results);    
}
