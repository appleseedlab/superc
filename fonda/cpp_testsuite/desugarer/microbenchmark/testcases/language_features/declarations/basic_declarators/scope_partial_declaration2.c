#ifdef A
int x;
// symtab: x -> int:A, undeclared:!A
#else
char x;
// symtab: x -> int:A, char:!A
#endif

int main() {
// this hides the "int x;" declaration in any configurations
#ifdef A
  float x;
// symtab: x -> float:A, char:!A&&!A  (int:!A&&A=False, i.e., no configurations)
#endif
  x++;
}
