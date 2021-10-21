#include <stdlib.h>

#define local_irq_enable()
#define local_irq_disable()
#define local_bh_enable()
#define local_bh_disable()

static inline void spin_lock_irq()
{
  local_irq_disable();
}

static inline void spin_unlock_irq()
{
  local_irq_enable();
}

static inline void spin_lock_bh()
{
  local_bh_disable();
}

static inline void spin_unlock_bh()
{
  local_bh_enable();
}

static inline void kunmap_skb_frag()
{
  #ifdef CONFIG_HIGHMEM
  local_bh_enable(); // ERROR
  #endif
}

unsigned int skb_checksum()
{
  unsigned int csum = 0;

  while (rand() % 2) {
    if (rand() % 2) {
      kunmap_skb_frag();
    }
  }

  return csum;
}

static int udp_checksum_complete()
{
  return skb_checksum();
}

unsigned int udp_poll()
{
  unsigned int mask = 0;

  spin_lock_irq();
  while (rand() % 2) {
    udp_checksum_complete();
  }
  spin_unlock_irq();

  return mask;
}

int main(int argc, char** argv)
{
  udp_poll();
  return 0;
}
