#define v(x, ...) x && __VA_ARGS__

#if v(A, B)
printf("hello world!\n");
#endif
