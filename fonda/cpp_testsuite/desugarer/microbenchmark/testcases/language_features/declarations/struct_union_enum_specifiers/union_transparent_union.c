typedef union {
  int* a;
  long b;
#ifdef TRANPARENT
} U __attribute__ ((__transparent_union__));
#else
} U
#endif

extern void foo(U);

#ifdef TRANPARENT
int main ()
{
  int x;
  foo (&x);
  return 0;
}
#endif
