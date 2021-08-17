#ifdef REPEATED
enum E {
        A, B, A,
};
#else
enum {
      A = 11,
      B = 11,
};
#endif
