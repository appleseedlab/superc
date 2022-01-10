int main() {
#ifdef A
  int x;
#else
  double x;
#endif

  x = 1;
  x++;

  #ifdef A
  int flag = sizeof(x) == 4;
  #else
  int flag = sizeof(x) == 8;
  #endif
  printf("%d\n", flag);
  
  return 0;
}
