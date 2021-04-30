#ifdef A
typedef signed int a;
#else
typedef unsigned int a;
#endif

int foo(a x)
{
  x++;
  return 0;
}

int main()
{
  foo(1);
  return 0;
}
