#ifdef A
#define NAME headerA
#else
#define NAME headerB
#endif

#define HEADER(x) x.h

#define str(x) #x

#define _str(x) str(x)

#include _str(HEADER(NAME))

