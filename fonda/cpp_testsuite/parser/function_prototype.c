#if !defined(CONFIG_ARCH_SUPPORTS_OPTIMIZED_INLINING) || \
    !defined(CONFIG_OPTIMIZE_INLINING) || (__GNUC__ < 4)
# define inline         inline          __attribute__((always_inline))
#endif

static inline int hash(int major, int minor, int ino)
{
        unsigned long tmp = ino + minor + (major << 3);
        tmp += tmp >> 5;
        return tmp & 31;
}
