typedef union {
  int* a;
  long b;
} U __attribute__ ((__transparent_union__));

extern void foo(U);

int main ()
{
  int x;
  foo (&x);
  return 0;
}
