#ifdef FUNCTION
#define f(x) (x + 1)
#else
#define f c_function
int c_function(int param) { return param + 1; }
#endif

int x = f
#ifdef A
(1)
#endif
  ;
