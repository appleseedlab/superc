int num = 1;

int main() {
  int x_1;
  int *x_2;

  if (A)
    x_1 = &num;
  else
    x_2 = &num;
  if (A)
    error();
  else
    *x_2;
  
  return 0;
}
