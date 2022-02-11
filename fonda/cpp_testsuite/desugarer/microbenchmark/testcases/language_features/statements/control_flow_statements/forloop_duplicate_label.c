int foo() {
  int ret = 1;
  for (int i = 0; i < 10; i++) {
#ifdef ENABLE_A
    if (i % 2) goto lab;
    ret++;
    lab:
    ret *= 2;
#endif
    ret++;
  }
  return ret;
}

int main() {
  return foo();
}
