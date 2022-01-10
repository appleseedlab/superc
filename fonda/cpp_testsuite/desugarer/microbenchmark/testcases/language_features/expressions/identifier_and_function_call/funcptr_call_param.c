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
#ifdef HAS_PARAM
  int (*ptr) (int) = foo;
  ptr(10);
#else
  int (*ptr) () = foo;
  ptr();
#endif
  return 0;
}
