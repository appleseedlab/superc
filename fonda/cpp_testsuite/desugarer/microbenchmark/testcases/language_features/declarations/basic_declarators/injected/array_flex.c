#include <stdio.h>

#ifdef A
#define __flexarr []
#endif
int a;
struct x {
  int x;
#ifdef A
  char name __flexarr;
#else
  char name[5];
#endif
};

int main() {
  #ifdef A
  int flag = sizeof(struct x) == 4;
  #else
  int flag = sizeof(struct x) == 12;
  #endif
  printf("%d\n", flag);
  return 0;
}
