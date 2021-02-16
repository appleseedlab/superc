struct s { int field1; };

int main() {
  int *x_1;
  struct s *x_2;

  if (A)
    *x_1;
  else
    *x_2;
  
  return 0;
}
