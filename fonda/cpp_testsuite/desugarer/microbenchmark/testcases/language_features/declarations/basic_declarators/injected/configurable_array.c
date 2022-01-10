int main() {
  #ifdef A
  int x[4];
  #else
  double x[5];
  #endif

  #ifdef A
  int flag = sizeof(x) == 16;
  #else
  int flag = sizeof(x) == 40;
  #endif
  printf("%d\n", flag);
  
  return 0;
}
