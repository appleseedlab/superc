struct T a;
struct X b;
#ifdef ENABLE_A
struct T {
  long field_t;
};
struct X {
  int field_x;
#ifdef ENABLE_B
  struct T field_struct_t;
#else
  char field_struct_t;
#endif
};
#else
struct X {
  int field_x;
};
struct T {
  int field_t;
  struct X field_struct_x;
};
#endif
int main() {
  return sizeof(struct X) + sizeof(struct T);
}
