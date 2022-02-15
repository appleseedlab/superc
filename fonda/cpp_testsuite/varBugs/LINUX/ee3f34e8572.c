#include <stdbool.h>
#include <stdlib.h>

#ifndef SCTP_DEBUG
#ifdef CONFIG_SCTP_DBG_MSG
#define SCTP_DEBUG      1
#else
#define SCTP_DEBUG      0
#endif /* CONFIG_SCTP_DBG */
#endif /* SCTP_DEBUG */

bool IS_ERR(const void *ptr)
{
  return (ptr == (void *)-1);
}

bool IS_ERR_OR_NULL(const void *ptr)
{
  return !ptr || IS_ERR(ptr);
}

#if SCTP_DEBUG
#define SCTP_DEBUG_PRINTK(ptr) ((*ptr)++)
#else
#define SCTP_DEBUG_PRINTK(ptr)
#endif

#if defined(CONFIG_IP_SCTP) && defined(CONFIG_IPV6)
static int some_int = 1;

int *ip6_dst_lookup_flow()
{
  return &some_int;
}

void sctp_v6_get_dst()
{
  int *dst = NULL;
  dst = ip6_dst_lookup_flow();
  if (!IS_ERR(dst)) {
    dst = NULL; // (2)
  }
  if (!IS_ERR(dst)) {
    char *rt =(char *) dst; // (3)
    SCTP_DEBUG_PRINTK(rt); // (4) ERROR
  }
}
#endif

int main()
{
#if defined(CONFIG_IP_SCTP) && defined(CONFIG_IPV6)
  sctp_v6_get_dst(); // (1)
  #endif
  return 0;
}
