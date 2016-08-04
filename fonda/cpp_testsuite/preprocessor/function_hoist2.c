#ifdef A
#define F(x, y) (x)+(y)
#else
#define F(x) 2*(x)
#endif

int num = F(
100
#ifdef A
,
200
#endif
  );
