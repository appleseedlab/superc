#include <errno.h>
#include <stdlib.h>

#ifdef CONFIG_PROC_PAGE_MONITOR

#define PM_ENTRY_BYTES sizeof(long)
#define PM_END_OF_BUFFER 1
#define NUM_ENTRIES 10

long *pm_buffer;
unsigned long pm_pos, pm_len;

static int add_to_pagemap()
{
  pm_buffer[pm_pos++] = 0; // (5,8) ERROR
  if (pm_pos >= pm_len) // (6) comparing array positions against bytes !!!
    return PM_END_OF_BUFFER;
  return 0;
}

static int pagemap_pte_range()
{
  int err = 0;

  while (1) {
    err = add_to_pagemap(); // (4,7)
    if (err)
      return err;
  }

  return err;
}

int walk_page_range()
{
  return pagemap_pte_range(); // (3)
}

static int pagemap_read() {
  pm_len = PM_ENTRY_BYTES * NUM_ENTRIES;
  pm_buffer = malloc(pm_len);

  if (!pm_buffer)
    return -ENOMEM;

  pm_pos = 0;
  walk_page_range(); // (2): note that pm_len units are bytes

  return 0;
}

#endif /* CONFIG_PROC_PAGE_MONITOR */

int main(int argc, char** argv) {
  #ifdef CONFIG_PROC_PAGE_MONITOR
  pagemap_read(); // (1)
  #endif
  return 0;
}
