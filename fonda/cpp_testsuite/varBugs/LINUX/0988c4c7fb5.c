#include <assert.h>

// To avoid constant propagation
__attribute__ ((noinline)) int nondet() { return 42; }

#ifdef CONFIG_VLAN_8021Q
_Bool vlan_hwaccel_do_receive()
{
  // do something
  return 1;
}
#else
_Bool vlan_hwaccel_do_receive()
{
  assert(0); // (4) ERROR
  return 0;
}
#endif

int __netif_receive_skb()
{
  if (nondet())
    {
      vlan_hwaccel_do_receive(); // (3)
    }
  return 0;
}

int netif_receive_skb()
{
  #ifdef CONFIG_RPS
  return __netif_receive_skb(); // (2)
  #else
  return __netif_receive_skb(); // (2)
  #endif
}

int main(void)
{
  netif_receive_skb(); // (1)
  return 0;
}
