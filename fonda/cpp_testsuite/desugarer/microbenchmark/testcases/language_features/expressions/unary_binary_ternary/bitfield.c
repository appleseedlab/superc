
struct x
{
#ifdef BITFIELD
  int field: 4;
#else
  int field;
#endif
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
