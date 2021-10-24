enum e {
  A = 1,
  B = 2,
  #ifdef X
  C,
};
  #else
  C,
};
#endif

