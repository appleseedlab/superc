#ifdef A
#define F(x, y) (x)*(y)
#else
#define F(x) (x)+1
#endif

int num = F(
2 +
#ifdef A
1,
7 +
#endif
3
  );
