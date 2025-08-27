struct x {
  int a;
  #ifdef ENABLE_A
  int b;
  #endif
  int c;
  int d;
};

int main(void) {
  struct x myFirstStruct = {1, 2, 3};
  return myFirstStruct.c;
}
