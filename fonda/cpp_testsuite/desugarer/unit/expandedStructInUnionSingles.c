struct S {
  #ifdef A
  int a;
  #else
  int a;
  #endif
};

union U{
  struct S one;
  int two;
  int three;
} u1;


int main() {

  int array[5-sizeof(u1)];
  return 0;
}
