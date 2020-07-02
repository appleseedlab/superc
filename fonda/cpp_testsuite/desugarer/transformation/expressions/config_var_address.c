int main(void) {
  int x = 5;
  int *y;

  #if A
    y = &x;
  #else
    y = 3;
  #endif

  return 0;
}
