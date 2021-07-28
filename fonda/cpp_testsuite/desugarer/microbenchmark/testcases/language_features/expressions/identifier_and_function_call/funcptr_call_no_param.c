int foo();

int foo() {
  return 1;
}

int main() {
  int (*ptr) () = foo;
  ptr();
  return 0;
}
