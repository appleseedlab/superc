#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IFNAMSIZ 16

typedef struct ethtable_s {
  struct ethtable_s *next;
  char *ifname;
} ethtable_t;

#ifdef ENABLE_FEATURE_CLEAN_UP
static void delete_eth_table(ethtable_t *ch)
{
  free(ch->ifname);
  free(ch);
};
#else
void delete_eth_table(ethtable_t *ch)
{
}
#endif

static void prepend_new_eth_table(ethtable_t **clist, char *ifname)
{
  ethtable_t *ch;
  if (strlen(ifname) >= IFNAMSIZ)
    printf("interface name '%s' too long", ifname);
  ch = malloc(sizeof(*ch));
  ch->ifname = ifname;
  ch->next = *clist;
  *clist = ch;
}

int main(int argc, char** argv)
{
  ethtable_t *clist = NULL;
  ethtable_t *ch;

  prepend_new_eth_table(&clist, argv[0]);

  #ifdef ENABLE_FEATURE_CLEAN_UP
  for (ch = clist; ch; ch = ch->next) // ERROR
    delete_eth_table(ch);
  #endif
  return 0;
}
