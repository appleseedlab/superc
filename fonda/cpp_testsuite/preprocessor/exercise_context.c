//(1) multiple macro definitions
//(2) conditional blocks
#if defined C1
#define M1 1
#else
#define M1 2
#endif

int x1 = M1;
int x2 = M1;

//(3) multiple function macro definitions
#if defined C2
#define F(x) (x)*(x)
#else
#define F(x) (x)+(x)
#endif

int x2 = F(3);

//(4) combine multiple
#if defined C3
#if defined C4
F(
#endif
#endif
3);


