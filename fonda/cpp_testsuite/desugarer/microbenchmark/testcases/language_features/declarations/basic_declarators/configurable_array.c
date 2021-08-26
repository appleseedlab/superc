int main() {
  #ifdef A
  int x[4];
  #else
  float x[5];
  #endif

  x[5];
  
  return 0;
}
