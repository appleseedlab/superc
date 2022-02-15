#include <stdio.h>
#include <stdlib.h>

void ap_log_perror_(int level)
{
  printf("%d\n", level);
}

#if __STDC_VERSION__ >= 199901L && defined(APLOG_MAX_LOGLEVEL)
#define ap_log_perror__(level)    \
  if (rand() % 2) { ap_do_log_perror_(level); } // ERROR: ap_do_log_perror_ undeclared
#endif

int main(void)
{
#if __STDC_VERSION__ >= 199901L && defined(APLOG_MAX_LOGLEVEL)
  ap_log_perror__(2);
  #endif
  return 0;
}
