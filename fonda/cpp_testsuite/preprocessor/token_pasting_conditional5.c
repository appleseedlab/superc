#define f(x) ID_ ## x

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
