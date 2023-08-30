#include <limits.h>
#include <stdint.h>

typedef int32_t  s32;
typedef int64_t  s64;
typedef uint64_t u64;

#ifdef CONFIG_64BIT
#define BITS_PER_LONG 64
#else
#define BITS_PER_LONG 32
#endif /* CONFIG_64BIT */

#define NSEC_PER_SEC 1000000000L

#define KTIME_MAX ((s64)~((u64)1 << 63))
#if (BITS_PER_LONG == 64)
#define KTIME_SEC_MAX (KTIME_MAX / NSEC_PER_SEC)
#else
#define KTIME_SEC_MAXLONG_MAX
#endif

#if (BITS_PER_LONG == 64) || defined(CONFIG_KTIME_SCALAR)

#define ktime_add_ns(nsval) (nsval)

#else/* !((BITS_PER_LONG == 64) || defined(CONFIG_KTIME_SCALAR)) */

static inline s64 ktime_set(const long secs)
{
  return (s64)secs * NSEC_PER_SEC;
}

s64 ktime_add_ns(u64 nsec)
{
  s64 tmp;

  if (nsec < NSEC_PER_SEC) {
    tmp = nsec;
  } else {
    unsigned long sec = nsec / NSEC_PER_SEC;
    tmp = ktime_set((s32)sec); // ERROR
  }

  return tmp;
}

#endif

static u64 tick_nohz_stop_sched_tick()
{
  u64 time_delta =(u64) 7881299347898368000;
  s64 expires;

  if (time_delta < KTIME_MAX)
    expires = ktime_add_ns(time_delta);
  else
    expires = KTIME_MAX;

  return expires;
}

int main(int argc, char** argv)
{
  tick_nohz_stop_sched_tick();
  return 0;
}
