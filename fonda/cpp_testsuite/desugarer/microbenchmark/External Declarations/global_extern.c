// since the function is both global and extern, configuration-aware link resolution is needed and cannot be handled on a per-compilation-unit basis
#ifdef CONFIG_A
int f(int x) {
  return x + 1;
}
#else
extern int f(int x);
#endif
