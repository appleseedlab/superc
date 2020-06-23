/*typedef
#ifdef T
int
#else
float
#endif
type;
*/
int foo(
#ifdef A
#ifdef B
        int x,
        #endif
        #endif
        #ifdef A
        #ifdef C
        int y,
        #endif
        #endif
        #ifdef A
        int z,
        #endif
        int w)
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
