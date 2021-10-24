#include <stdio.h>
#include <stdlib.h>

long rmm_addr = 99999999999999999;

char* apr_rmm_addr_get(char *ptr)
{
  *ptr = '\0';
  return ptr;
}

void util_ald_alloc()
{
  #if APR_HAS_SHARED_MEMORY
  /* allocate from shared memory */
  char* buf = apr_rmm_addr_get((char*)calloc(rmm_addr, sizeof(char)));
  printf("%s\n", buf);
  #else
  // do something
  #endif
}

void util_ald_create_cache()
{
  util_ald_alloc();
}

void util_ald_create_caches()
{
  util_ald_create_cache();
}

int main(void)
{
  util_ald_create_caches();
  return 0;
}
