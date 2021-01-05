int main() {
  #ifdef A
  int x_1[4];
  #else
  struct { int field1; } x_2;
  #endif

  if (A)
    error();
  else
    x_2.field1;
  
  return 0;
}
