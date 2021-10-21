#include <stdio.h>

#ifdef HAVE_FIPS
int fips;
#endif

void ssl_init_Module()
{
  if (fips == 0)
    printf("Something");
}

int main(void)
{
  ssl_init_Module();
  return 0;
}
