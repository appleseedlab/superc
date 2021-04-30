#ifdef A
typedef int a;
#endif

#ifdef B
typedef int b;
#endif

#ifdef C
typedef int c;
#endif

void foo(
  #ifdef C
  a x, c z,
 #endif
#ifdef B
    b y
#endif
         )
{
  #ifdef A
  x = 2;
  #endif
  #ifdef B
  y = 2;
  #endif
  #ifdef C
  z = 2;
  #endif
  return;
}

int main()
{
  return 0;
}
