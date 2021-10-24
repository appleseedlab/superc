struct x {
  int a;
  int b;
  union {
#ifdef A
    int c;
    long * d;
#else
    short c;
    int * d;
#endif
  };
};

int main ()
{
  struct x x;
  int a = x.c;
  return 0;
}
