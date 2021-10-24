struct x_1 {
  int a_2;
  int b_3;
  int c_4;
  int c_5;
};

static int A;
int main(void) {

  struct x_1 myFirstStruct_6 = {.a_2 = 1,
                                .b_3 = ( A ? 2 : 0),
                                .c_4 = (!A ? 2 : 0),
                                .c_5 = 0};

  return 0;
}
