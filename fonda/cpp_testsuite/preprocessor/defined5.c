//fully defined
#ifdef CONFIG1
#define MACRO 1
#else
#define MACRO 0
#endif

#if defined MACRO
#endif

#if defined MACRO && UNDEF
#endif

