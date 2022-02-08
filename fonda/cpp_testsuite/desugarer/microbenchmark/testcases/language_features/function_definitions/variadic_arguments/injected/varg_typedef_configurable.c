#ifdef ENABLE_A
typedef int x;
#else
typedef double x;
#endif

#include <stdarg.h>

x foo(int num, ...) {
  x sum = 0;
  va_list valist;
  va_start(valist, num);
  for (int i = 0; i < num; i++) {
#ifdef ENABLE_A
    sum += va_arg(valist, int);
#else
    sum += va_arg(valist, double);
#endif
  }
  va_end(valist);
  return sum;
}

int main() {
  return sizeof(foo(2, 1, 3));
}
