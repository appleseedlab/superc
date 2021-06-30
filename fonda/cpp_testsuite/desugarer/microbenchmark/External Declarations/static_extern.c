// since the function is external, the renamed function needs to be defined to just call the external function by its original name, but the static method needs no such definition since it isn't external.
#ifdef CONFIG_A
static int f(int x) {
  return x + 1;
}
#else
extern int f(int x);
#endif
