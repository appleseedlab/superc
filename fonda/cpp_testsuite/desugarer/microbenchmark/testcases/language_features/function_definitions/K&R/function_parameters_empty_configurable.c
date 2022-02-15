int f(
#ifdef B
      x,
#ifdef A
      y,
#endif
      z
#else
      a
#endif
      )
#ifdef B
      int x;
#ifdef A
      int y;
#endif
      int z;
#else
      int a;
#endif
{}
