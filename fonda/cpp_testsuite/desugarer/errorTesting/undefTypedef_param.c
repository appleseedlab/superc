#ifdef A
typedef int x;
#endif

void foo (
#ifdef A
  x a
  #else
  x b
  #endif
          ) {
  return;
}

int main( )
{
  foo (1);
  return 0;
}
