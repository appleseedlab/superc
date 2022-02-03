int main() {
  #ifdef A
  int x[4];
  #else
  float x[5];
  #endif

  x[3];
  
  return 0;
}
