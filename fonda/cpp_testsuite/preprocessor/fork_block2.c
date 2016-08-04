#ifdef BOB
#define F(x) (x)
#else
#define F(x) 27 * (x)
#endif

F(
#ifdef C1
arg1
#else
arg2
#endif
#ifdef C2
C2
#else
notc2
#endif
)

