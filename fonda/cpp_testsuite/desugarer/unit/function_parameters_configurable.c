int f(char x
      #ifdef A
      , int y
      #endif
      ) {
  #ifdef B
  int x;
  #endif
  int z;

  y = x + y;

  z = y;

  return z;
}
