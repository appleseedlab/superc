#define f(x) cpu(x) cpu(x)
#define cpu(x) bob(x)

#if defined A
#define bob(x) something(x)
#endif

f(SINGLE)

f(f(NESTED)))
