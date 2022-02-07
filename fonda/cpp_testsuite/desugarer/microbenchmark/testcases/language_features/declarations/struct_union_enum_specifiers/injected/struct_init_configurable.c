struct x {
  int a;
  #ifdef ENABLE_A
  int b;
  #endif
  int c;
};

int main(void) {
  struct x myFirstStruct = {1, 2};
  return myFirstStruct.c;
}
