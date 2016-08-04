#define R R 1
#define f(x) x | R
f(R)

f(f(R))

#define Y y
#define recursive(x) x Y
#define g(x) x | recursive(x)
g(recursive(a) recursive(Y))


#define h(R) R
h(R)
