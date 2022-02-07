#ifdef ENABLE_A
int foo(int a);
#else
int foo();
#endif

int foo(int a) {
  return a;
}

int main() {
  foo(1);
  return 0;
}
