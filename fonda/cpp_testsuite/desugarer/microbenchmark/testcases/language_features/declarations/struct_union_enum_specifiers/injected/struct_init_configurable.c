struct x {
  int a;
  #ifdef ENABLE_A
  int b;
  #endif
  int c;
};

int main(void) {

  // under PC A: a = 1 and b = 2
  // under PC !A: a = 1 and c = 2
  struct x myFirstStruct = {1, 2};

  #ifdef ENABLE_A
  int flag = myFirstStruct.b == 2;
  #else
  int flag = myFirstStruct.c== 2;
  #endif
  return flag;
}
