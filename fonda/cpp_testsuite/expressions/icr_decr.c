int main(void) {
#if A
  int x;
#else
  char x;
#endif

  x = 1;

  x++;
  x--;

  int y;

  y = x;

  ++y;
  --y;

  return 0;
}
