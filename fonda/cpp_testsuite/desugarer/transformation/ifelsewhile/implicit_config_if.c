int main(void) {
  #if A
    int x = 2;
  #else
    char x = 3;
  #endif

  if (x == 2) {
    x++;
  }

  return 0;
}
