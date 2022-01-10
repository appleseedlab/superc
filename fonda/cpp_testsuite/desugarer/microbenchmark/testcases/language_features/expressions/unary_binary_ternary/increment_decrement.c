int main() {
  int x;
  if (x) {
#ifdef A
    x++;
#endif
  } else {
#ifdef B
    x--;
#endif
  }
  return 0;
}
