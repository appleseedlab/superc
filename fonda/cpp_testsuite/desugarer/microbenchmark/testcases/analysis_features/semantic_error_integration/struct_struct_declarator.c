int main() {
  #ifdef A
  struct { char a; } x;
  #else
  struct { int field1; } x;
  #endif

  x.a;
  
  return 0;
}
