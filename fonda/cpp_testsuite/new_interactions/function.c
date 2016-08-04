#ifdef A
#define F(x) x
#elif defined B
#define F(x, y) (x)+(y)
#else
int F(int x, int y) {
  return x+y;
}
#endif

#ifdef A
int x = F(1);
#else
int x = F(1, 2);
#endif
