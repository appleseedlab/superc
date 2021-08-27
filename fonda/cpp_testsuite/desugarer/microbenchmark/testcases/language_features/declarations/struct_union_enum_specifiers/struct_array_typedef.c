# define _SIGSET_NWORDS (1024 / (8 * sizeof (unsigned long int)))
typedef struct {
  unsigned long int a[_SIGSET_NWORDS];
} Y;

struct X {
  Y b;
};

#ifdef A
typedef struct X testStruct[1];
testStruct x;
#endif
