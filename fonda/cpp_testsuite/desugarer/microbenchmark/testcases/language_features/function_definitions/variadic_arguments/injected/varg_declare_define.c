#include <stdarg.h>

#ifdef ENABLE_A
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

int main() {
  #ifdef ENABLE_A
  return foo(4, 2, 3, 4, 5);
  #else
  return foo(2, 1, 2);
  #endif

}
