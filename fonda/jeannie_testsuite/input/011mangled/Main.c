#include <jni.h>
#include "mangledcasts.h"
int printf(const char*, ...);

struct C {
  jint* pa;
};

void JNICALL Java_Main_f(JNIEnv *env, jclass cls) {
  jint a=0, b=0;
  b = ({
    struct C c;
    c.pa = &a;
    jmethodID mid = (*env)->GetStaticMethodID(env, cls, "c2j", "(J)I");
    jint result = (*env)->CallStaticIntMethod(env, cls, mid, env2long(&c));
    a = *(c.pa);
    result;
  });
  printf("%d, %d\n", (int)a, (int)b);
}

jint JNICALL Java_Main_j2c(JNIEnv *env, jclass cls, jlong pci) {
  struct C* pc = long2env(pci, C);
  return (jint)(*(pc->pa) = 1);
}
