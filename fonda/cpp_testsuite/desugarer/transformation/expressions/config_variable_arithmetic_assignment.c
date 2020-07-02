int main(void) {
  #if A
    int x;
  #else
    char x;
  #endif

  #if B
    int y;
  #else
    char y;
  #endif

  x = 1;
  y = 2;

  x += y;

  x -= y;

  x *= y;

  x /= y;

  x %= y;

  return 0;
}
