// since the function is both global and extern, configuration-aware link resolution is needed and cannot be handled on a per-compilation-unit basis.  the static version needs no handling for global linkage.
#ifdef CONFIG_A
int f(int x) {
  return x + 1;
}
#elif CONFIG_B
static int f(int x) {
  return x + 1;
}
#else
extern int f(int x);
#endif
