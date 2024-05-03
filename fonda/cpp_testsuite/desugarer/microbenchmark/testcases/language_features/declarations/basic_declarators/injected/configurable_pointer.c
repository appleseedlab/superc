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

  return sizeof(*x);
}
