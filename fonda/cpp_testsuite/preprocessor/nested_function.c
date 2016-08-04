#define func1(x) (FUNC ONE (x))
#ifdef A
#define func2() (FUNC TWO A)
#else
#define func2() (FUNC TWO B)
#endif

func1(func2())

#define funcp(x) #x

funcp(func2())
