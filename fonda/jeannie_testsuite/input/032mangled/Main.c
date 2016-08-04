#include <jni.h>
#include <stdio.h>

struct CEnv {
  int a;
  int* b;
  int* c;
};

void JNICALL Java_Main_j2c(JNIEnv* env, jclass cls) {
  struct CEnv cEnv;
  struct CEnv* pcEnv = &cEnv;
  pcEnv->a = 2;
  int tb[pcEnv->a];
  pcEnv->b = tb;
  int tc[pcEnv->a - 1];
  pcEnv->c = tc;
  pcEnv->b[0] = 11;
  pcEnv->b[1] = 22;
  pcEnv->c[0] = 33;
  printf("%d %d %d %d\n", pcEnv->a, pcEnv->b[0], pcEnv->b[1], pcEnv->c[0]);
}
