int main() {
  printf("redeclarations under some configurations");
#ifdef A
  int x;
#endif
#ifdef OKAY
  int x;
#endif
  return 0;
}
