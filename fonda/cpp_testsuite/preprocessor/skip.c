#ifdef A
#define M 1
#define F(x) (x)
#define G(x) *x
#else
#define M 2
#define F(x) [x]
#define G(x) q(x)
#endif

F(M)

//-------

#ifdef B
#define N 7
#define E() e1
#else
#define N 8
#define E() e2
#endif

F(N)

//------

G(F(x))

//------

G(E())
