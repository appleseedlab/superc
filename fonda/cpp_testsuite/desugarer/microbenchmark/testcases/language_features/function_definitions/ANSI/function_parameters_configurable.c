int f(char x
#ifdef A
      , int y
#endif
      ) {
  int z = x
#ifdef A
        + y
#endif
;
  return z;
}
