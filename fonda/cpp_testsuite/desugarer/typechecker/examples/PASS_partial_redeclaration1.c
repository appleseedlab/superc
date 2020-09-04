int main() {
  //  printf("redeclarations under some configurations");
#ifdef A
  int x;
#endif
#ifdef B
  char x;
#endif
  return 0;
}
