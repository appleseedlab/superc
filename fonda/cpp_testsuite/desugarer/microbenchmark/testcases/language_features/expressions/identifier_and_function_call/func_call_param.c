#ifdef HAS_PARAM
int foo(int a);

int foo(int a) {
  return a;
}
#else
int foo();

int foo() {
  return 1;
}
#endif

int main() {
  int z;
#ifdef HAS_PARAM
  z = foo(10);
#else
  z = foo();
#endif
  return z;
}
