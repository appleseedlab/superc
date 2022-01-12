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
  #ifdef ENABLE_A
  #ifdef ENABLE_B
  int flag = sizeof(struct X) == 16;
  #else
  int flag = sizeof(struct X) == 8;
  #endif
  #else
  int flag = sizeof(struct T) == 8;
  #endif
  return flag;
}
