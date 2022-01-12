struct s { 
  int field1; 
  int field2;
};

int main() {
  #ifdef ENABLE_A
  int *x;
  #else
  struct s *x;
  #endif

  #ifdef ENABLE_A
  int flag = sizeof(*x) == 4;
  #else
  int flag = sizeof(*x) == 8;
  #endif
  return flag;
}
