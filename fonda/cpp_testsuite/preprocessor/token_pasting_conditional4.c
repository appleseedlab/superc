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





