#define __gcc_header(x) #x
#define _gcc_header(x) \
__gcc_header(linux/compiler-gcc##x.h)
#define gcc_header(x) _gcc_header(x)
#include gcc_header(__GNUC__)

