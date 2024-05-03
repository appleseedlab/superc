int main() {
  int x = x;
  #ifdef A
  x = 2;
#else
  x = 3;
  #endif
  return x;
}
