extern int foo();

#ifdef ENABLE_A
int foo() {
  return 0;
}
#endif

int main() {
  #ifdef ENABLE_A
  return foo();
  #else
  return 1;
  #endif
}
