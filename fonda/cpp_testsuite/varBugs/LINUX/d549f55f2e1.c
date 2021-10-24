#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef CONFIG_VLAN_8021Q
void* vlan_dev_real_dev()
{
  return NULL;
}
#else
void* vlan_dev_real_dev()
{
  assert(false); // (3) ERROR
  return NULL;
}
#endif

#if defined(CONFIG_IPV6) || defined(CONFIG_VLAN_8021Q)
static int ocrdma_inet6addr_event()
{
  vlan_dev_real_dev(); // (2)

  return 0;
}
#endif /* IPV6 and VLAN */

int main(int argc, char** argv)
{
#if defined(CONFIG_IPV6) || defined(CONFIG_VLAN_8021Q)
  ocrdma_inet6addr_event(); // (1)
  #endif
  return 0;
}
