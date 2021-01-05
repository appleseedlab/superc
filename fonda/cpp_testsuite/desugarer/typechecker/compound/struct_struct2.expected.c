int main() {
  struct { char a; } x_1;
  struct { int field1; } x_2;

  if (A)
    error();
  else
    x_2.field1;
  
  return 0;
}
