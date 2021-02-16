struct { char a; } x_1;
char x_2(int y) {
  return y;
}

int main() {
  if (A)
    error();
  else
    x_2(2);
  return 0;
}
