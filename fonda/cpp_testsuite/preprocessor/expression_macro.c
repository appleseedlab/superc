#ifdef CONFIG_64BIT
#define BITS_PER_LONG 64
#else
#define BITS_PER_LONG 32
#endif /* CONFIG_64BIT */

//from kernel/sched.c which indirectly includes bitsperlong.h
#if BITS_PER_LONG == 32
# define WMULT_CONST    (~0UL)
#else
# define WMULT_CONST    (1UL << 32)
#endif

int c = WMULT_CONST;

