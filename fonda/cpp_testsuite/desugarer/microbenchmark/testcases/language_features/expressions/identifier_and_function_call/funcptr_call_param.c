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
  int (*ptr) (int) = foo;
  z = ptr(10);
#else
  int (*ptr) () = foo;
  z = ptr();
#endif
  return z;
}
