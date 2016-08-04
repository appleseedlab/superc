#define FOO 1 ## 2 ## 3
FOO
#define f(x) PREFIX_ ## x ## _SUFFIX
f(1 2 3)
f(1 2 x)
