int num = 5;

int main() {
  #ifdef A
  int *x;
  #else
  char x[5];
  #endif

  x = &num;
  *x;
  
  return 0;
}
