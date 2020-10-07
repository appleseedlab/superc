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
  float x;
// symtab: x -> float:B, int:!B&&A, char:!B&&!A
#endif
  x++;
}
