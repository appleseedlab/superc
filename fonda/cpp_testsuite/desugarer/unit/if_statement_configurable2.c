int main() {
  int x, y, z;
  if (x) {
#ifdef A
    x++;
#endif
#ifdef B
    y++;
#endif
#ifdef C
    z++;
#endif
  }
}
