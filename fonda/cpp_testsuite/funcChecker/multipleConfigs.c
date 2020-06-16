typedef
#ifdef T
int
#else
float
#endif
type;

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
        type z,
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
foo(w)
foo(x,int z,w)
foo(y,int z,w)
foo(x,y,int z,w)
foo(x,float z,w)
foo(y,float z,w)
foo(x,y,float z,w)
 */
