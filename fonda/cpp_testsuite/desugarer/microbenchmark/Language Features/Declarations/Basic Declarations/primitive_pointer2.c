int num = 1;

int main() {
  #ifdef A
  int x;
  #else
  int *x;
  #endif

  x = &num;
  *x;
  
  return 0;
}
