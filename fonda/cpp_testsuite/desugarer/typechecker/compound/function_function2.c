#ifdef A
float x(float a, float b) {
  return a * b;
}
#else
char x(int y) {
  return y;
}
#endif

int main() {
  x(7);
  return 0;
}
