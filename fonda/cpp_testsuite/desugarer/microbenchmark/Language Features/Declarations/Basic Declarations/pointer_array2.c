int num = 5;

int main() {
  #ifdef A
  int *x;
  #else
  char x[5];
  #endif

  x[2];
  
  return 0;
}
