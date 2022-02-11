int f(
#ifdef ENABLE_B
      int x,
#ifdef ENABLE_A
      int y,
#endif
      int z
#else
      int a
#endif
      ) {
}

int main() {
  int k;
  #ifdef ENABLE_B
  #ifdef ENABLE_A
  k = f(1, 2, 3);
  return 6;
  #else
  k = f(1, 3);
  return 3;
  #endif
  #else
  k = f(4);
  return 4;
  #endif
}
