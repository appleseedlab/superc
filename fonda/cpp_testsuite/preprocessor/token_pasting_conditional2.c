#define f(x) ID_ ## x

int f(
#ifdef A
#ifdef B
1
#else
2
#endif
#else
3
#endif
);



int f(
#ifdef X
a
#else
#ifdef Y
b
#elif defined Z
c
#else
d
#endif
#endif
);
