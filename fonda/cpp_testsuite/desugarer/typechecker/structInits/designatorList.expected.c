struct x {
  int a_1;
  unsigned a_2;
};
struct y {
  struct x a_3;
  int b_4;
};
int main ()
{
  struct y a_5;
  if (A)
    a_5.a_3.a_1 = 2;
  if (!A)
    a_5.a_3.a_2 = 2;
  return 0;
}
