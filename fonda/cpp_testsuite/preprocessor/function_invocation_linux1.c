#define LOCK_CONTENDED_FLAGS(_lock, try, lock, lockfl, flags) \
        lockfl((_lock), (flags))

#ifdef CONFIG_DEBUG_SPINLOCK
#define do_raw_read_lock_flags(lock, flags) do_raw_read_lock(lock)
#else
# define do_raw_read_lock_flags(lock, flags) \
		arch_read_lock_flags(&(lock)->raw_lock, *(flags))
#endif


LOCK_CONTENDED_FLAGS(lock, do_raw_read_trylock, do_raw_read_lock,
                     do_raw_read_lock_flags, &flags);
