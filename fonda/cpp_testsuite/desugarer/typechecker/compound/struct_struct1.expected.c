int main() {
  struct { char a; } x_1;
  struct { int field1; } x_2;

  if (A)
    x_1.a;
  else
    error();
  
  return 0;
}
