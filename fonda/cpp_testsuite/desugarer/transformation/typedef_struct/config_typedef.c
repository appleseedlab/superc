#if A
typedef int typeAlias;
#else
typedef char typeAlias;
#endif

struct bob {
  typeAlias val;
  char otherVal;
};
