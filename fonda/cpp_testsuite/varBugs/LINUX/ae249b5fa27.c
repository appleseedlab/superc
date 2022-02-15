#include <stdbool.h>

#ifdef CONFIG_DISCONTIGMEM
#include <assert.h>
#include <string.h>
#endif

#define PFNNID_MAP_MAX  512     /* support 512GB */
unsigned char pfnnid_map[PFNNID_MAP_MAX];
unsigned long max_pfn = PFNNID_MAP_MAX;

#ifdef CONFIG_DISCONTIGMEM
int pfn_to_nid(unsigned long pfn)
{
  unsigned char r;

  assert(pfn < PFNNID_MAP_MAX);
  r = pfnnid_map[pfn];
  assert(r != 0xff); // (6) ERROR: all positions set to 0xff by (2)

  return (int)r;
}

int pfn_valid(int pfn)
{
  int nid = pfn_to_nid(pfn); // (5)

  return (nid >= 0);
}
#endif

#ifndef CONFIG_DISCONTIGMEM
#define pfn_valid(pfn)(true)
#endif /* CONFIG_DISCONTIGMEM */

#ifdef CONFIG_PROC_PAGE_MONITOR
int kpageflags_read()
{
  unsigned int pfn = 0;

  for (;pfn<max_pfn;pfn++) {
    if (pfn_valid(pfn)) // (4)
      ;
  }

  return 0;
}
#endif

void setup_bootmem(void)
{
  #ifdef CONFIG_DISCONTIGMEM
  memset(pfnnid_map, 0xff, sizeof(pfnnid_map)); // (2) pfnnid_map[*] = 0xff
  #endif
}

int main()
{
  setup_bootmem(); // (1)
  #ifdef CONFIG_PROC_PAGE_MONITOR
  kpageflags_read(); // (3)
  #endif
  return 0;
}
