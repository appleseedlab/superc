int main(void) {
  #if A
    int x;
  #else
    char x;
  #endif

  #if B
    unsigned int y;
  #else
    unsigned char y;
  #endif
  
  int z;
  int w;
  int u;
  int v;

  #if C
    long t;
  #else
    short t;
  #endif

  x = 2;
  y = 3;
  z = 5;
  w = 1;
  u = 7;
  v = 6;
  t = 8;

  x = y + z - w * u / v % t;

  return 0;
}
