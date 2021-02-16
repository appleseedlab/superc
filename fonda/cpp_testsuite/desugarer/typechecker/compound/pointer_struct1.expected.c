int num = 5;

int main() {
  int *x_1;
  struct { int field1; } x_2;

  if (A)
    x_1 = &num;
  else
    error();
  if (A)
    *x_1;
  else
    error();
  
  return 0;
}
