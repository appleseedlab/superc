int num = 1;

#ifdef A
int *x_1;
#else
char x_2(int y) {
  return y;
}
#endif

int main() {
  if (A)
    x_1 = &num;
  else
    error();
  if (A)
    *x_1;
  else
    error();
  
  return 0;
}
