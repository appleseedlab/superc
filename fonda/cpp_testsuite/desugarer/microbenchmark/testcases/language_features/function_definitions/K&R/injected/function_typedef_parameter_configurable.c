#ifdef ENABLE_A
typedef int x;
#else
typedef double x;
#endif

int foo(a)
  x a;
{
  return sizeof(a);
}

int main()
{
  return foo(0);
}
