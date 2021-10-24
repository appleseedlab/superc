#ifdef A
typedef int a;
#endif

#ifdef B
typedef int b;
#endif

#ifdef C
typedef int c;
#endif

struct y
{
#ifndef A
  a i;
  b j;
#endif
#ifdef B
  c k;
  #endif
};


int main()
{
 #ifdef B
  int d = 2;
  #else
  int d = 2;
#endif
  return 0;
}
