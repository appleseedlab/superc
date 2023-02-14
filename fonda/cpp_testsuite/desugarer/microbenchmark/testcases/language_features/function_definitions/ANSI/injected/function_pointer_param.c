int foo(int fn()) {
  return fn();
}

int f1() {
  return 4;
}

int f2() {
  return 5;
}

int main () {
  return foo(
#ifdef A
             f1
#else
             f2
#endif
);
}
