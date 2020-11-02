// since f is global, a multiplexer dispatches f to the correct version of the function
#ifdef CONFIG_A
int f(int x) {
  return x + 1;
}
#else
int f(int x) {
  return x - 1;
}
#endif
