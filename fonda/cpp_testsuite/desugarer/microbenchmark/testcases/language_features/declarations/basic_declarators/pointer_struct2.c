int num = 5;

int main() {
  #ifdef A
  int *x;
  #else
  struct { int field1; } x;
  #endif

  x.field1;
  
  return 0;
}
