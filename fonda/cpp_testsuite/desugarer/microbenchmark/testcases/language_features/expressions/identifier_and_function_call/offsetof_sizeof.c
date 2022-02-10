#include <stddef.h>

#ifdef OFFSETOF
struct t { int y; char z; } bob;

size_t x = offsetof(struct t, z);
#endif

#ifdef SIZEOF
long l;

size_t y = sizeof(l);
#endif
