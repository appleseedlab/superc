#define f(x,y) x ## y

int f(
#ifdef A
a
#else
b
#endif
,
#ifdef N
1
#else
2
#endif
);
