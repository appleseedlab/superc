#include <stdarg.h>

#ifdef ENABLE_A
int foo(int num, ...) {
  int sum = 0;
  va_list valist;
  va_start(valist, num);
  for (int i = 0; i < num; i++) {
    sum += va_arg(valist, int);
  }
  va_end(valist);
  return sum;
}
#endif

int main() {
  #ifdef ENABLE_A
    return foo(2, 1, 3) + foo(3, 1, 2, 3);
  #else
    return 0;
  #endif  
}

