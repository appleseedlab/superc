int main() {
  int x;
  #ifdef A
  x++;
  #endif
  #ifdef B
  x--;
  #endif
  return 0;
}
