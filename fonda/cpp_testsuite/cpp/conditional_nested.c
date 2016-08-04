#define M 1
#define N 2

#if defined M
#if defined N
HELLO WORLD!
#else
WRONG1
#endif
#else
WRONG2
#endif


#if defined(__ppc__)
#  if defined(__LDBL_MANT_DIG__) && defined(__DBL_MANT_DIG__) && \
	__LDBL_MANT_DIG__ > __DBL_MANT_DIG__
#    if __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__-0 < 1040
#      define	__DARWIN_LDBL_COMPAT(x)	__asm("_" __STRING(x) "$LDBLStub")
#    else
#      define	__DARWIN_LDBL_COMPAT(x)	__asm("_" __STRING(x) "$LDBL128")
#    endif
#    define	__DARWIN_LDBL_COMPAT2(x) __asm("_" __STRING(x) "$LDBL128")
#    define	__DARWIN_LONG_DOUBLE_IS_DOUBLE	0
#  else
#   define	__DARWIN_LDBL_COMPAT(x) /* nothing */
#   define	__DARWIN_LDBL_COMPAT2(x) /* nothing */
#   define	__DARWIN_LONG_DOUBLE_IS_DOUBLE	1
#  endif
#elif defined(__i386__) || defined(__ppc64__) || defined(__x86_64__) || defined (__arm__)
#  define	__DARWIN_LDBL_COMPAT(x)	/* nothing */
#  define	__DARWIN_LDBL_COMPAT2(x) /* nothing */
#  define	__DARWIN_LONG_DOUBLE_IS_DOUBLE	0
#else
#  error Unknown architecture
#endif
