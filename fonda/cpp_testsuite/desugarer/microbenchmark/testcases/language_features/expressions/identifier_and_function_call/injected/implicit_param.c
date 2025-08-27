#ifdef ENABLE_A
typedef signed int a;
#else
typedef long a;
#endif

int foo(a x)
{
  x++;
  return sizeof(a);
}

int main()
{
  return foo(1);
}
