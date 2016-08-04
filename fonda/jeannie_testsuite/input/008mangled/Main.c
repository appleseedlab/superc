#include <jni.h>
#include <stdlib.h>

int printf(const char*, ...);

typedef struct List {
  int item;
  struct List* next;
} List;

int twice(int k) {
  return 2 * k;
}

void JNICALL Java_Main_sayHi(JNIEnv *env, jclass clazz) {
  /* ------------------------------------------------------------------ */
  printf("  Some Types\n");
  {
    char* s;
    char c;
    int i;
    float f;
    int* a;
    List* l;
    s = "hello";
    printf("    s is \"%s\"\n", s);
    c = 'g';
    printf("    c is '%c'\n", c);
    i = 2 * 7;
    printf("    i is %d\n", i);
    f = 3.141f;
    printf("    f is %f", f);
    a = malloc(3 * sizeof(int));
    a[0] = 2;
    a[1] = 9;
    a[2] = 0;
    printf("    a is {%d, %d, %d}\n", a[0], a[1], a[2]);
    l = malloc(sizeof(List));
    l->item = 4;
    l->next = 0x0;
    printf("    l is { item=%d, next=0x0 }\n", l->item);
  }
  /* ------------------------------------------------------------------ */
  printf("  Some Statements\n");
  {
    int i,j;
    i = 4;
    i = twice(i);
    printf("    i is %d\n", i);
    j = 1;
    while(j<1000)
      j = j + j;
    printf("    j is %d\n", j);
    if(j < 300000)
      printf("    j < 300,000\n");
    else
      printf("    j >= 300,000\n");
    printf("    countdown");
    for(i=10; i>=1; i--)
      printf(" %d", i);
    printf("\n");
  }
  /* ------------------------------------------------------------------ */
}
