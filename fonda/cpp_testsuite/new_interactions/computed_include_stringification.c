#ifdef A
#define FILE computed_include_header1.h
#else
#define FILE computed_include_header2.h
#endif

#define _str(x) #x
#define str(x) _str(x)

#include str(FILE)

