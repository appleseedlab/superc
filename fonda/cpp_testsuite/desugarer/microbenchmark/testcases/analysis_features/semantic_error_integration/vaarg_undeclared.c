#include <stdarg.h>
#ifdef A
int x;
#endif

int main()
{
  va_arg(x,int*);
}
