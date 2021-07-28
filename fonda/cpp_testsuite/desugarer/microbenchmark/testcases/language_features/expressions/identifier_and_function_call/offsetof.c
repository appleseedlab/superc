#include <stddef.h>

struct t { int y; char z; } bob;

size_t x = offsetof(struct t, z);
