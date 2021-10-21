#include <stdio.h>

void status_handler()
{
  long x = 2147483644;
  long y = 2147483645;

  #ifndef HAVE_TIMES
  printf("%f %ld",
         #else
         printf("%ld %ld",
                #endif

                (long) x, (long) y);
         }

    void register_hooks()
    {
      status_handler();
    }

  int main(void)
  {
    register_hooks();
    return 0;
  }
