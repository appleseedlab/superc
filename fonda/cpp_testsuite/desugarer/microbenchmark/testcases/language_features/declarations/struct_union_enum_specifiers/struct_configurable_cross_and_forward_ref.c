struct T bob;
#ifdef CONFIG_A
struct T {
  int field_t;
};
struct X {
  int field_x;
  #ifdef CONFIG_B
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
  #ifndef CONFIG_A
  bob.field_struct_x;
  #else
  bob.field_t;
  #endif
}
