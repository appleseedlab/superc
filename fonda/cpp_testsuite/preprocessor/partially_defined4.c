#ifdef A
#define f _f
#else
int f(int param) { return -1; }
#endif


#ifdef FUNCTION
#define _f(x) (x + 1)
#else
#define _f c_function
int c_function(int param) { return param + 1; }
#endif

int x = f(1);
