int main(void) {
  #if A
    int x;
  #else
    char x;
  #endif

  x = 3 + 5 - 6 * 4 / 2 % 7;

  return 0;
}
