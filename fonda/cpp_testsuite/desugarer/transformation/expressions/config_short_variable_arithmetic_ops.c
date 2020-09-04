int main(void) {

  #if A
    int x;
  #else
    char x;
  #endif

  int y;
  int z;
  x = 1;
  y = 2;
  z = 3;

  x = y + z;

  x = y - z;

  x = y * z;

  x = y / z;

  x = y % z;

  return 0;
}
