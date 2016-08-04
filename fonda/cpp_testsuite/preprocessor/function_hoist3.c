#ifdef A
#define F(x, y) x+y
#else
#define F(x) 2*x
#endif

int num = F(
#ifdef B
7000 + 20 * -50
#else
100
#endif
#ifdef A
,
200
#endif
  );
