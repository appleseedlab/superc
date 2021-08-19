#ifdef X
#define TT this.a
#else
#define TT this.b
#endif

union u {
    struct
    {
      int num;
    } a;
    struct
    {
      int x;
    } b;
} this;

void foo()
{
  int i, wlen = TT.num;

  for (i;;) {
  flush:
    i=2;
  }
}
