#ifdef A
int x[5];
#else
char x(int y) {
  return y;
}
#endif

int main() {
  x(2);
  return 0;
}
