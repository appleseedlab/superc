#if (defined __KERNEL__)
F;
#endif



#if !(defined __LINUX_SPINLOCK_TYPES_UP_H)

#if (defined CONFIG_DEBUG_SPINLOCK)
A;
#elif 1
B;
#endif

#endif

#if !(defined __LINUX_LOCKDEP_H)
#if (defined CONFIG_TRACE_IRQFLAGS)
C;
#endif
#endif

