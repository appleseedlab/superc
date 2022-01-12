#ifdef ENABLE_A
int x;
// symtab: x -> int:A, undeclared:!A
#else
char x;
// symtab: x -> int:A, char:!A
#endif

int main() {
// this hides the "int x;" declaration in any configurations
#ifdef ENABLE_A
  double x;
// symtab: x -> float:A, char:!A&&!A  (int:!A&&A=False, i.e., no configurations)
#endif
  x++;

#ifdef ENABLE_A
  int flag = sizeof(x) == 8;
#else
  int flag = sizeof(x) == 1;
#endif
  return flag;
}
