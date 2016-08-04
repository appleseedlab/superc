//partially defined
#ifdef CONFIG1
#define MACRO 1
ZERO
#endif

#if defined MACRO
ONE
#endif

#if defined MACRO && UNDEF
TWO
#endif

