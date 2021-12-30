#ifdef A
typedef signed int a;
#else
typedef unsigned int a;
#endif

int foo(a x)
{
  x++;
  return x;
}

int main()
{ int z;
  z = foo(1);
  return z;
}
