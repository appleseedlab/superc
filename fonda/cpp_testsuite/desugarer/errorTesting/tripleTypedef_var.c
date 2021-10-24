#ifdef A
typedef int a;
#endif

#ifdef B
typedef int b;
#endif

#ifdef C
typedef int c;
#endif


int main()
{
#ifndef A
  a i;
  b j;
#endif
#ifdef B
  c k;
#endif
  return 0;
}
