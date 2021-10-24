struct x
{
  int field: 4;
};

int main() {
  struct x a,*b;
  if (a.field) {
    int i = 0;
  }
  if (b->field) {
    int i = 0;
  }
  return 0;
}
