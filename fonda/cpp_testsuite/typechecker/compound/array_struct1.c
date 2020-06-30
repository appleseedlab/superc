int main() {
  #ifdef A
  int x[4];
  #else
  struct { int field1; } x;
  #endif

  x[2];
  
  return 0;
}
