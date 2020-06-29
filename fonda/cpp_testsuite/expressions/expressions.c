
int main(void) {
#if A
  int x;
#else
  char x;
#endif

  int y;
  int z;

  y = 2;
  z = 4;

  x = 3 + 5;

  x = x + z - y;

  x = x / 4;

  x = 2 * y;

  x = z % 5;

  x += 1;

  x -= 2;

  x *= 5;

  x /= 3;

  x %= 4;

  return 0;
}
