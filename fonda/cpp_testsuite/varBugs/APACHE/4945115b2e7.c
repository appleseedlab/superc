#include <stdio.h>
#include <stdlib.h>

void run_cgi_child()
{
  #ifdef DEBUG_CGI
  #ifdef OS2
  FILE *dbg = fopen("con", "w");
  #else
  FILE *dbg = fopen("/dev/tty", "w");
  #endif
  #endif

  #ifdef DEBUG_CGI
  fprintf(dbg, "Environment\n");
  #endif

  if(rand() % 2)
    return; // ERROR: dbg is leaked

  #ifdef DEBUG_CGI
  fclose(dbg);
  #endif
  return;
}

void cgi_handler()
{
  run_cgi_child();
}

int main(void)
{
  cgi_handler();
  return 0;
}
