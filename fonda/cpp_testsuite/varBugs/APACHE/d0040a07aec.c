#include <stdio.h>
#include <stdlib.h>

#if defined (RLIMIT_CPU) || defined (RLMIT_NPROC) || defined (RLIMIT_DATA) || defined(RLIMIT_VMEM) || defined(RLIMIT_AS)
int limits;
#endif

void send_req()
{
  #ifdef RLIMIT_NPROC
  limits = (rand() % 2) ? 1 : 0; // ERROR: limits not declared
  printf("%d", limits);
  #endif
}

int main(void)
{
  send_req();
  return 0;
}
