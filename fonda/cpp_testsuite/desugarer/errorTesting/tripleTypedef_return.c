#ifdef A
typedef int a;
#endif

#ifdef B
typedef int b;
#endif

#ifdef C
typedef int c;
#endif

#ifdef B
c
#endif
#ifdef A
b
#endif
foo();

int main()
{
  foo();
  return 0;
}
