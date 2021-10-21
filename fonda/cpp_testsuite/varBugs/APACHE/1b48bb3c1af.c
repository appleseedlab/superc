#include <stdio.h>

void apr_rmm_init(char* rmm_lock)
{
  printf("%s\n", rmm_lock);
}

#ifdef APU_HAS_LDAP
void util_ldap_cache_init()
{
  char* rmm_lock;

  #ifdef APR_HAS_SHARED_MEMORY
  apr_rmm_init(rmm_lock); // ERROR: rmm_lock uninitialized
  #endif
}
#endif

int main(void)
{
    #ifdef APU_HAS_LDAP
  util_ldap_cache_init();
    #endif
  return 0;
}
