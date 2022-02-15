int main () {
  ((union {int a; long b;}){.a = 2}).b;
  return 0;
}
