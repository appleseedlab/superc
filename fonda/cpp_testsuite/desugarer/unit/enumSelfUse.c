#ifdef X
//#define FEATURE(z) z = 20
#else
#define FEATURE(z) z = 30
#endif
enum {
  A,
  B,
  FEATURE(C),
  A_1 = 1 << A,
  B_1 = 1 << B,
};
