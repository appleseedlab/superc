#ifdef A
typedef int x;
#endif

#ifdef A
x foo (){ return 1;}
#else
x foo (){ return 2;}
#endif

int main()
{
  foo();
  return 0;
}
