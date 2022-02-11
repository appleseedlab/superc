#ifdef ENABLE_A
int foo(int a);
#else
int foo();
#endif

#ifdef ENABLE_A
int foo(a) 
  int a;
{
  return a;
}
#else
int foo() {
  return 0;
}
#endif

int main() {
  #ifdef ENABLE_A
  return foo(2);
  #else
  return foo();
  #endif 
}
