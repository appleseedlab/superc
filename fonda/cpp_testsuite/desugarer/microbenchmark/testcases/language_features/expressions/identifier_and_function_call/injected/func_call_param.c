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
  return foo(10);
#else
  return foo();
#endif
}
