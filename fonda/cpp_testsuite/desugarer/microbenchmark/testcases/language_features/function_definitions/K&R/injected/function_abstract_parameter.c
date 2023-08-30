#ifdef ENABLE_A
int foo();

int foo(x)
  int *x;
{
  return 1;
}
#endif

int main() {
  #ifdef ENABLE_A
  return foo(0);
  #else
  return 0;
  #endif
}
