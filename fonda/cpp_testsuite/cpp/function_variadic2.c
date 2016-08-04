#define variadic(a, b, args...) int x = a; int y = b; printf(args);


variadic(1, 2, "hello %d %d\n", x, y);
