struct a {
  int a_1;
  #ifdef A
  int b_2;
  #endif
  int c_3;
};

struct b {
  int a_4;
  struct a field_5;
};

int main()
{
  struct b bee = {1,{2,3}};
  if (1) {
    bee.a_4 = 1;
    if (A) {
      bee.field_5.a_1 = 2;
      bee.field_5.b_2 = 3;
    }
    if (!A) {
      bee.field_5.a_1 = 2;
      bee.field_5.c_3 = 3;
    }
  }
  return 0;
}
