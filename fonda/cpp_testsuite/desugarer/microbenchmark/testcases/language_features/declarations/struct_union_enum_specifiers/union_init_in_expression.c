int main () {
#ifdef UNIONINIT
  ((union {int a; long b;}){.a = 2}).b;
#endif
  return 0;
}
