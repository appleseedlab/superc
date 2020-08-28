int main() {
  int x, y, z;
  if (x) {
    x--;
#ifdef A
    x++;
#endif
#ifdef B
    y++;
#endif
#ifdef C
    z++;
#endif
    z--;
  }
}
