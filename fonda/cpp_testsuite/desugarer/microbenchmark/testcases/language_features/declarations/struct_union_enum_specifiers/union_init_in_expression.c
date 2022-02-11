int main () {
#ifdef ENABLE_A
  return ((union {int a; long b;}){.a = 2}).b;
#endif
  return 0;
}
