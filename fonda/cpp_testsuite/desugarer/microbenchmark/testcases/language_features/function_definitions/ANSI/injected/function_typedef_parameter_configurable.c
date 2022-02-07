#ifdef ENABLE_A
typedef int x;
#else
typedef double x;
#endif

int foo(x a)
{
  return sizeof(x);
}

int main()
{
  return foo(0);
}
