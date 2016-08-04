//(1) logical negation
#if ! defined C
int x = 1;
#endif

//(2) logical and
#if defined A && defined B
int y = 1
#endif

//(3) logical or
#if defined D || defined E
int z = 1;
#endif

//(4) partially defined
#if defined A
#define PART
#elif defined B
#undef PART
#endif

#if defined PART
int a = 1;
#endif

//(5) inline conditional expression
#if defined C1 ? defined C2 : defined C3
int b = 1;
#endif

