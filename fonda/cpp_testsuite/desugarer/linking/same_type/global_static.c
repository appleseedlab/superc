// only the global version of the function should be dispatched in the global multiplexer
#ifdef CONFIG_A
int f(int x) {
  return x + 1;
}
#else
static int f(int x) {
  return x - 1;
}
#endif
