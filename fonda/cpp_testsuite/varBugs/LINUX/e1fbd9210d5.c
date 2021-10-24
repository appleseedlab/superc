#include <stdio.h>

#ifdef CONFIG_LBDAF
typedef unsigned long long sector_t;
#else
typedef unsigned long sector_t;
#endif

sector_t blk_rq_pos() {
  return 0;
}

#ifdef CONFIG_AMIGA_Z2RAM
static void do_z2_request() {
  printf("bad access: block=%lu\n", blk_rq_pos()); // ERROR
}
#endif

int main() {
    #ifdef CONFIG_AMIGA_Z2RAM
  do_z2_request();
    #endif
  return 0;
}
