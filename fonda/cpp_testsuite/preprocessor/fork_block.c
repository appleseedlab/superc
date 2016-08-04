#ifdef BOB
#define F(x) (x)
#else
#define F(x) 27 * (x)
#endif

#define BUFFER_SIZE 1024
#ifdef DOUBLE
  #define BUFFER_SIZE 2048
#endif
foo = (char *) malloc (BUFFER_SIZE);

F(
#ifdef C1
arg1
#else
arg2
#endif
BUFFER_SIZE
)

