#ifdef ENABLE_A
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
#ifdef ENABLE_A
  int (*ptr) (int) = foo;
  return ptr(10);
#else
  int (*ptr) () = foo;
  return ptr();
#endif
}
