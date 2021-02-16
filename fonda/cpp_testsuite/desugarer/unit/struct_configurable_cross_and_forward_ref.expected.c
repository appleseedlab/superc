struct T_1 bob_6;
struct T_5 bob_7
struct T_1 {
  int field_t;
};
struct X_2 {
  int field_x;
  struct T_1 field_struct_t;
};
struct X_3 {
  int field_x;
  char field_struct_t;
};
struct X_4 {
  int field_x;
};
struct T_5 {
  int field_t;
  struct X_4 field_struct_x;
};
int main() {
  if (!CONFIG_A)
    bob_7.field_struct_x;
  if (CONFIG_A)
    bob_6.field_t;
}
