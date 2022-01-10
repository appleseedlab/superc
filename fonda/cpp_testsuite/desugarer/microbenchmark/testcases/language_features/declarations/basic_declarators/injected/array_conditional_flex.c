#include <stdio.h>

#ifdef A
typedef int x;
#else
typedef short x;
#endif

int main() {
  x id[2] = {1, 2};
  #ifdef A
  int flag = sizeof(id) == 8;
  #else
  int flag = sizeof(id) == 4;
  #endif
  printf("%d\n", flag);
}
