#if A
typedef int typeAlias;
#else
typedef char typeAlias;
#endif

typedef struct bob {
  typeAlias val;
  char otherVal;
} bob;
