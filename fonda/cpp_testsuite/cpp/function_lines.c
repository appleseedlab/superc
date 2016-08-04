#define f(x) x

f(__LINE__)

f(
  __LINE__)

f(__LINE__
__LINE__
__LINE__
  )

#ifdef A
#undef f
#endif

f(__LINE__
  __LINE__
  __LINE__)
