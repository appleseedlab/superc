int main() {
  #ifdef A
  int x;
  #else
  char x[5];
  #endif

  x = 1;
  x++;
  
  return 0;
}
