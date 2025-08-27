#ifdef ENABLE_A
int foo (int a, ...)
#else
int foo (int a, int b, int c, int d)
#endif
{
  
}

int main () {
  #ifdef ENABLE_A
  foo (1, 2);
  return 3;
  #else
  foo (1, 2, 3, 4);
  return 10;
  #endif
}
