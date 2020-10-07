int main(void) {
  #if A
    int x;
  #else
    char x;
  #endif

  x = 3;

  x += 1;

  x -= 2;

  x *= 5;

  x /= 3;

  x %= 4;

  return 0;
}
