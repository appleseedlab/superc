#include <stdio.h>

#ifdef SIGPIPE
#define SIGPIPE 1
#endif

void apr_signal_block(int signal)
{
  printf("%d\n", signal);
}

int main(void)
{
  apr_signal_block(SIGPIPE); // ERROR: SIGPIPE undeclared
  return 0;
}
