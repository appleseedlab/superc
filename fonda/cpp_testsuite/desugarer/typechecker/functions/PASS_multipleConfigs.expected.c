/*typedef
#ifdef T
int
#else
float
#endif
type;
*/
int foo_1(x,y,z,w)
{
  return 0;
}
int foo_2(x,z,w)
{
  return 0;
}
int foo_3(y,z,w)
{
  return 0;
}
int foo_4(z,w)
{
  return 0;
}
int foo_5(w)
{
  return 0;
}

int main()
{
  return 0;
}

/*
  foo(w)                  -!A && (!B || B) && (!C || C)
  foo(x,z,w)              -A && B && !C
  foo(y,z,w)              -A && !B && C
  foo(x,y,z,w)            -A && B && C
  foo(z,w)                -A && !B && !C
 */
