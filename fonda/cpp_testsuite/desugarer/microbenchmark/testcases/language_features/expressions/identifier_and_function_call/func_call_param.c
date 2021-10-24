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
  foo(10);
#else
  foo();
#endif
  return 0;
}
