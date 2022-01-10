#ifdef A
int x;
// symtab: x -> int:A, undeclared:!A
#else
char x;
// symtab: x -> int:A, char:!A
#endif

int main() {
  // this does not hide "int x;" declaration in all configurations
#ifdef B
  double x;
// symtab: x -> float:B, int:!B&&A, char:!B&&!A
#endif
  x++;

#ifdef B
  int flag = sizeof(x) == 8;
#else 
#ifdef A
  int flag = sizeof(x) == 4;
#else
  int flag = sizeof(x) == 1;
#endif
#endif
  printf("%d\n", flag);
}
