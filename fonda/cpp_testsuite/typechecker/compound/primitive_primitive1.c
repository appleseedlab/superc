int main() {
  #ifdef A
  int x;
  #else
  float x;
  #endif

  x = 1;
  x++;
  
  return 0;
}
