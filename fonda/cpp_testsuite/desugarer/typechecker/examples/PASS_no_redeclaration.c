int main() {
#ifdef A
  int x;
#endif
  //  printf("no redeclaration in any configuration");
#ifdef A
  x++;
#else
  char x;
  x--;
#endif
}
