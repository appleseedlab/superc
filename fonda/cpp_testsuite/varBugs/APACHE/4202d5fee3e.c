#include <stdio.h>

#ifdef APU_HAS_LDAP
char certtdb = 'A';

void util_ldap_connection_open()
{
  #ifdef APU_HAS_LDAP_NETSCAPE_SSL
  printf("%c", certdb); // ERROR: certdb undeclared
  #endif
}
#endif

int main(void)
{
  #ifdef APU_HAS_LDAP
  util_ldap_connection_open();
  #endif
  return 0;
}
