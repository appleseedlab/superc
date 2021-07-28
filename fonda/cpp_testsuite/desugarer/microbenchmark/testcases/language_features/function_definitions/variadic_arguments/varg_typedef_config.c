#ifdef A
typedef int x;
#else
typedef float x;
#endif

#include <stdarg.h>

x foo(int num, ...) {
  x sum = 0;
  va_list valist;
  va_start(valist, num);
  for (int i = 0; i < num; i++) {
#ifdef A
    sum += va_arg(valist, int);
#else
    sum += va_arg(valist, double);
#endif
  }
  va_end(valist);
  return sum;
}
