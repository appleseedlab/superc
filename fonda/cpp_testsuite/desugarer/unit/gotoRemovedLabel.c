#ifndef X
#define X 2
#endif
#ifndef Y
#define Y 3
#endif
int a;
int b;

int main() {
  if (a > b)
    goto L;

  switch (a) {
  case X:
  L:
    a = 3;
    break;
  case Y:
    a = 4;
  default:
    b=1;
  }
  return 0;
}
