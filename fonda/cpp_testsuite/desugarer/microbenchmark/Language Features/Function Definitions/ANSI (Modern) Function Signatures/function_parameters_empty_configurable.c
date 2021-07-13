int f(
#ifdef B
      int x,
#ifdef A
      int y,
#endif
      int z
#else
      int a
#endif
      ) {
}
