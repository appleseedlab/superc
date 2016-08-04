#include <jni.h>
#include <stdio.h>

struct s {
  int a[3];
  int b;
};

struct CEnv {
  struct s x;
};

void JNICALL Java_Main_j2c(JNIEnv* env, jclass cls) {
  struct CEnv cEnv;
  struct CEnv* pcEnv = &cEnv;
  pcEnv->x = (struct s) { .a = { 1, 2, 3}, .b = 4 };
  printf("%d %d %d %d\n",
         pcEnv->x.a[0], pcEnv->x.a[1], pcEnv->x.a[2], pcEnv->x.b);
}
