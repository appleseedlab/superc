int num = 1;

#ifdef A
int *x;
#else
char x(int y) {
  return y;
}
#endif

int main() {
  x = &num;
  *x;
  
  return 0;
}
