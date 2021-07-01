int main() {
  #ifdef A
  int x;
  #else
  char x[5];
  #endif

  x[0] = 1;
  
  return 0;
}
