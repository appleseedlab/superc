int foo(int a) {
  if ( a == 0) {
    return 1;
  }
  return foo(a-1)
    #ifdef A
    *
#else
    +
    #endif
    2;
}

int main() {
  return foo(5);
}
