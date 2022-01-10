struct s { 
  int field1; 
  int field2;
};

int main() {
  #ifdef A
  int *x;
  #else
  struct s *x;
  #endif

  #ifdef A
  int flag = sizeof(*x) == 4;
  #else
  int flag = sizeof(*x) == 8;
  #endif
  printf("%d\n", flag);
  
  return 0;
}
