struct x {
  int a;
  int b;
};

enum sizes {
  A = sizeof(struct x),
  B = sizeof(union U{int a; long b;}),
  C
};

int main()
{
  enum sizes s;
  return 0;
}
