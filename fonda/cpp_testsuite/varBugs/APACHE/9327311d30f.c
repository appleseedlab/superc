#include <string.h>

char *rmm_addr;

void util_ald_create_cache(char *rmm_addr)
{
  #if APR_HAS_SHARED_MEMORY
  strcat(rmm_addr, "something");
  #else
  // do something
  #endif
}

void util_ald_create_caches(char *rmm_addr)
{
  util_ald_create_cache(rmm_addr);
}

int main(void)
{
  util_ald_create_caches(rmm_addr);
  return 0;
}
