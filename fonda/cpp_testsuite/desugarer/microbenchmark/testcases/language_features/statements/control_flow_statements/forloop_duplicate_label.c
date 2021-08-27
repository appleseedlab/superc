int foo() {
  int ret = 0;
  for (int i = 0; i < 10; i++) {
#ifdef A
    lab:
    ret *= 2;
#endif
    ret++;
  }
  return ret;
}
