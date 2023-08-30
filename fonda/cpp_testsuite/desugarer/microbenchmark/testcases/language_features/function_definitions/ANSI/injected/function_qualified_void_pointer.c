int foo( void *
#ifdef A
__restrict
#endif
         field) {
  #ifdef A
  return 3;
  #else
  return 2;
  #endif
}

int main() {
  int * x;
  return foo(x);
}
