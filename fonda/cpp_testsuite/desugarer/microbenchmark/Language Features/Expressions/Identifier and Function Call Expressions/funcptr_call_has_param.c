int foo();

int foo(int a) {
  return a;
}

int main() {
  int (*ptr) (int) = foo;
  ptr(10);
  return 0;
}
