#ifdef A
int x = 1;
#else
long x = 2;
#endif
int main() {
  int a, b = x;

  #ifdef A
  int flag = a == 0 && b == 1;
  #else
  int flag = a == 0 && b == 2;
  #endif
  printf("%d\n", flag);
  
}
