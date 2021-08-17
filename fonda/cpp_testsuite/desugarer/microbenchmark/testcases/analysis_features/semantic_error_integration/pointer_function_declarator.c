#ifdef A
int *x;
#else
char x(int y) {
  return y;
}
#endif

int main() {
  x(2);
  return 0;
}
