struct x
{
  #ifdef A
  int a_1;
#else
  unsigned a_2;
#endif
  #ifdef B
  int b_3;
  #endif
};

int main()
{
  struct x x;
  if (A && !B) {
    x.a_1 = 1;
    typeError();
  }
  if (!A && B) {
    x.a_2 = 1;
    x.b_3 = 2;
  }
  if (!A && !B) {
    x.a_2 = 1;
    typeError();
  }
  if (A && B) {
    x.a_1 = 1;
    x.b_3 = 2;
  }


  return 0;
}
