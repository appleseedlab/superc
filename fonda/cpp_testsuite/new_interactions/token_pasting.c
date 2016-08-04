#ifdef A
#define MACRO a
#else
#define MACRO b
#endif

#define _ID(x) ID_ ## x
#define ID(x) _ID(x)

int ID(MACRO);
