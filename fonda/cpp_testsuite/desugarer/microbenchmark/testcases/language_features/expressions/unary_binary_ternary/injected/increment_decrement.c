int main() {
  int x = 10;
  #ifdef ENABLE_A
  x++;
  #else
  x--;
  #endif
  return x;
}
