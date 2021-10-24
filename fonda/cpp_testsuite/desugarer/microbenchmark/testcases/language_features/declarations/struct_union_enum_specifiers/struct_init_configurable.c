struct x {
  int a;
  #ifdef A
  int b;
  #endif
  int c;
};

int main(void) {

  // under PC A: a = 1 and b = 2
  // under PC !A: a = 1 and c = 2
  struct x myFirstStruct = {1, 2};

  return 0;
}
