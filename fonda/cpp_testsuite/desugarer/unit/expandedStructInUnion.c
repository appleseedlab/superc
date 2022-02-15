struct S {
  #ifdef A
  int a;
  int b;
  #else
  int a;
  int b;
  #endif
};

union U{
  struct S one;
  int two;
  long long three;
} u1;


int main() {

  int array[9-sizeof(u1)];
  return 0;
}
