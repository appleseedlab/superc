int f(char x
#ifdef ENABLE_A
      , int y
#endif
      ) {
  int z = x
#ifdef ENABLE_A
        + y
#endif
;
  return z;
}

int main() {
  return f(1 
  #ifdef ENABLE_A
  , 2
  #endif
  );
}
