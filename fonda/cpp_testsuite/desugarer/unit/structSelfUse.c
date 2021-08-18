#ifdef X
//#define FEATURE(z) z = 20
#else
#define FEATURE(z) z
#endif
struct {
  int A;
  int B;
  int FEATURE(C);
  int A_1;
  int B_1;
};
