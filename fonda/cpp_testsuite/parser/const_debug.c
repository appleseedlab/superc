// From linux-3.2.9/arch/x86/include/asm/cache.h#L10
#define __read_mostly __attribute__((__section__(".data..read_mostly")))

// From linux-3.2.9/kernel/sched.c
#ifdef CONFIG_SCHED_DEBUG
# define const_debug __read_mostly
#else
# define const_debug static const
#endif

const_debug unsigned int sysctl_sched_nr_migrate = 32;
