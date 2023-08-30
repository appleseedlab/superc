#include <stddef.h>

#ifdef ENABLE_A
struct t { int y; char z; } bob;
size_t x = offsetof(struct t, z);
#else
long l;
size_t x = sizeof(l);
#endif

int main() {
  return x;
}
