#ifdef CONFIG_LOCKDEP
#define LOCK_CONTENDED_FLAGS(_lock, try, lock, lockfl, flags) \
        LOCK_CONTENDED((_lock), (try), (lock))
#else /* CONFIG_LOCKDEP */
#define LOCK_CONTENDED_FLAGS(_lock, try, lock, lockfl, flags) \
        lockfl((_lock), (flags))
#endif /* CONFIG_LOCKDEP */

#ifdef CONFIG_LOCK_STAT
#define LOCK_CONTENDED(_lock, try, lock)			\
do {								\
	if (!try(_lock)) {					\
		lock_contended(&(_lock)->dep_map, _RET_IP_);	\
		lock(_lock);					\
	}							\
	lock_acquired(&(_lock)->dep_map, _RET_IP_);			\
} while (0)
#else /* CONFIG_LOCK_STAT */
#define lock_contended(lockdep_map, ip) do {} while (0)
#define lock_acquired(lockdep_map, ip) do {} while (0)
#define LOCK_CONTENDED(_lock, try, lock) \
	lock(_lock)
#endif /* CONFIG_LOCK_STAT */

#ifdef CONFIG_DEBUG_SPINLOCK
#define do_raw_read_lock_flags(lock, flags) do_raw_read_lock(lock)
#else
# define do_raw_read_lock_flags(lock, flags) \
		arch_read_lock_flags(&(lock)->raw_lock, *(flags))
#endif


LOCK_CONTENDED_FLAGS(lock, do_raw_read_trylock, do_raw_read_lock,
                     do_raw_read_lock_flags, &flags);
