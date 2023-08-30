struct x;

int foo(struct x *a);
int z;
#ifdef A
struct x {
  int field;
};
#else
struct x {
  char field;
};
#endif

int main () {
  struct x data;
  data.field = 300;
  return foo(&data);
}

int foo(struct x * b) {
  return b->field;
}
