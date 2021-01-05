int num = 5;

int main() {
  int *x_1;
  char x_2[5];

  if (A)
    x_1 = &num;
  else
    error();
  if (A)
    *x_1;
  else
    *x_2;
  
  return 0;
}
