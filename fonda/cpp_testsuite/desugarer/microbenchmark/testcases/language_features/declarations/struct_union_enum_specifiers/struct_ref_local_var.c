#ifdef A
struct a;
struct a *foo(void);

void test_function() {
	struct a *x;
	x = foo();
}
#else

typedef long unsigned int size_t;
void *malloc(size_t n);
struct a;
typedef struct a b;
char *foo(b *x, const char *y, size_t z) {
  malloc((size_t) 1);
  char *Buffer = malloc((z + 16) % -16);
  return Buffer;
}
#endif
