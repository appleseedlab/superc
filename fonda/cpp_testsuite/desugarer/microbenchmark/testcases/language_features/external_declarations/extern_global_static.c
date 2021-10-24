#ifdef A
int f(int x) {
  return x + 1;
}
#elif B
static int f(int x) {
  return x + 1;
}
#else
extern int f(int x);
#endif
