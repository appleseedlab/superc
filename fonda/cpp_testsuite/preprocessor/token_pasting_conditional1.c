#ifdef CONFIG1
#define OBJECT config1
#else
#define OBJECT config2 * 3
#endif

#define f(x) x ## OBJECT

int x = f(OBJECT);



char y =

f(
#ifdef PASTE_CONFIG
OBJECT
#else
different
#endif
)

  ;





#define g(x) OBJECT ## x

double z =

  g(
#ifdef PASTE_CONFIG
OBJECT
#else
different
#endif
)

  ;





