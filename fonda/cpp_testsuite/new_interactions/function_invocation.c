#define _f(x, y) (x)+(y)

#ifdef A
#define f _f
#else
int f(int x, int y) {
  return x+y;
}
#endif

int x = f(1, 2);
