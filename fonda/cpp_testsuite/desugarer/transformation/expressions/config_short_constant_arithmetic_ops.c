int main(void) {
  #if A
    int x;
  #else
    char x;
  #endif

  x = 3 + 5;

  x = 2 - 1;

  x = 6 * 4;

  x = 8 / 2;

  x = 10 % 5;

  return 0;
}
