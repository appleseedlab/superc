int num = 5;

int main() {
  #ifdef A
  int *x;
  #else
  struct { int field1; } x;
  #endif

  x = &num;
  *x;
  
  return 0;
}
