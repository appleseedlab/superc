struct s { int field1; };

int main() {
  #ifdef A
  int *x;
  #else
  struct s *x;
  #endif

  *x;
  
  return 0;
}
