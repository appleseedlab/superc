int main() {
  #ifdef A
  int x;
  #else
  struct { int field1; } x;
  #endif

  x = 1;
  x++;
  
  return 0;
}
