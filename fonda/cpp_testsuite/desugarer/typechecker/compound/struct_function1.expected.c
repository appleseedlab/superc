struct { char a; } x_1;
char x_2(int y) {
  return y;
}

int main() {
  if (A)
    x_1.a;
  else
    error();
  return 0;
}
