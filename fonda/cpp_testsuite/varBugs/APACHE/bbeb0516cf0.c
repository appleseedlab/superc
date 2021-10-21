#include <stdlib.h>
#include <string.h>

void cgi_bucket_create(char *r)
{
  strcat(r, "something");
}

void cgi_handler(char *r)
{
  #if APR_FILES_AS_SOCKETS
  cgi_bucket_create(r);
  #endif
}

int main(void)
{
  char *r = NULL;
  cgi_handler(r);
  return 0;
}
