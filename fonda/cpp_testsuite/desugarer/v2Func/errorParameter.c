int foo(int a, int b)
{
  return 0;
}

int main()
{
  int a = 1;
  int b =
    #ifdef A
    c;
  #else
  1;
  #endif
  int c = c;
  int d = foo(a,b);
  d = foo(a,c);
  return 0;
}
