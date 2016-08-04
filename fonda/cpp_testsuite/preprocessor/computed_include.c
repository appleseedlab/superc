#ifdef A
#define NAME bob
#else
#define NAME noxious
#endif

#define HEADER(x) <x.h>

#include HEADER(NAME)

