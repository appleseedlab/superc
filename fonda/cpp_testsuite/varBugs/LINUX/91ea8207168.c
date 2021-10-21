#include <assert.h>
#include <string.h>

#ifdef CONFIG_NODES_SHIFT
// NB: parisc's CONFIG_NODES_SHIFT default is 3
#define NODES_SHIFT     CONFIG_NODES_SHIFT
#else
#define NODES_SHIFT     0
#endif

#define MAX_NUMNODES    (1 << NODES_SHIFT)

#define node_end_pfn(nid) NODE_DATA(nid)

#define MAX_PHYSMEM_RANGES 8 /* Fix the size for now (current known max is 3) */

#ifdef CONFIG_DISCONTIGMEM

int node_data[MAX_NUMNODES];

#define NODE_DATA(nid)          (node_data[nid])

#define PFNNID_MAP_MAX  512     /* support 512GB */
unsigned char pfnnid_map[PFNNID_MAP_MAX];
unsigned long max_pfn = PFNNID_MAP_MAX;

int pfn_to_nid(unsigned int pfn)
{
  assert(pfn < PFNNID_MAP_MAX);
  return (int)pfnnid_map[pfn];
}

int pfn_valid(unsigned int pfn)
{
  int nid = pfn_to_nid(pfn);

  if (nid >= 0)
    return (pfn < node_end_pfn(nid)); // ERROR
  return 0;
}

#endif

#ifndef CONFIG_DISCONTIGMEM
#define max_pfn 0
#define pfn_valid(pfn)(1)
#endif /* CONFIG_DISCONTIGMEM */

void setup_bootmem(void)
{
  #ifdef CONFIG_DISCONTIGMEM
  memset(pfnnid_map, 0xff, sizeof(pfnnid_map));
  #endif
}

#ifdef CONFIG_PROC_PAGE_MONITOR
int kpageflags_read()
{
  unsigned int pfn = 0;

  for (;pfn<max_pfn;pfn++) {
    if (pfn_valid(pfn))
      ;
  }

  return 0;
}
#endif

int main()
{
  setup_bootmem();
  #ifdef CONFIG_PROC_PAGE_MONITOR
  kpageflags_read();
  #endif
  return 0;
}
