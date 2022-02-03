typedef union {
  int* a;
  long b;
#ifdef TRANSPARENT
} U __attribute__ ((__transparent_union__));
#else
} U;
#endif

extern void foo(U);

#ifdef TRANSPARENT
int main ()
{
  int x;
  foo (&x);
  return 0;
}
#endif
