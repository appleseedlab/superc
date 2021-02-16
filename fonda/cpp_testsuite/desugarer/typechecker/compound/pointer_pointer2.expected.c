struct s { int field1; };

int main() {
  int *x_1;
  struct s *x_2;
  if (A)
    error();
  else
    (*x_2).field1;
  
  return 0;
}
