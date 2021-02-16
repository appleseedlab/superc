float x_1(float a, float b) {
  return a * b;
}
char x_2(int y) {
  return y;
}
int main() {
  if (A)
    x_1(3.2, 4.0);
  else
    error();
  return 0;
}

