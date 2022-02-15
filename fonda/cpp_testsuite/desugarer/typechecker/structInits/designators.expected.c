struct x
{
  int a_1;
  unsigned a_2;
  int b_3;
  unsigned b_4;
};

int main()
{
  struct x x;
  if (A && !B) {
    x.a_1 = 1;
    x.b_4 = 2;
  }
  if (!A && B) {
    x.a_2 = 1;
    x.b_3 = 2;
  }
  if (!A && !B) {
    x.a_2 = 1;
    x.b_4 = 2;
  }
  if (A && B) {
    x.a_1 = 1;
    x.b_3 = 2;
  }
  
  return 0;
}
