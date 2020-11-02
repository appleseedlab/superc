// since there is no linkage required, no multiplexing function is needed
#ifdef CONFIG_A
static int f(int x) {
  return x + 1;
}
#else
static int f(int x) {
  return x - 1;
}
#endif
