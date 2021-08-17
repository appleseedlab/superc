#include <stdarg.h>

#ifdef DECLARE
int foo(int num, ...);
#endif

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
