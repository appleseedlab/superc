#ifdef A
struct { char a; } x;
#else
char x(int y) {
  return y;
}
#endif

int main() {
  x(2);
  return 0;
}
