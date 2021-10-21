#include <stdlib.h>

#define APR_SUCCESS 1
#define EEXIST 2

int *cache = NULL;
int *util_ldap_shm;

int apr_shm_attach(int **util_ldap_shm)
{
  if (cache) {
    *util_ldap_shm = cache;
    return 0;
  }
  return -1;
}

int apr_shm_create(int **util_ldap_shm)
{
  if (cache)
    return EEXIST;
  cache = malloc(sizeof(int));
  *util_ldap_shm = cache;
  return 0;
}

int util_ldap_cache_init()
{
  #if APR_HAS_SHARED_MEMORY
  int result = apr_shm_create(&util_ldap_shm);
  if (result != APR_SUCCESS) {
    return result;
  }
  #endif
  return APR_SUCCESS;
}

int main(void)
{
  if (rand() % 2) {
    cache = malloc(sizeof(int));
  }
  util_ldap_cache_init();
  return 0;
}
