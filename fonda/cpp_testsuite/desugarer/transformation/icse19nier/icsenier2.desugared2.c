bool CONFIG_QUOTA; /* originally a macro */

struct t_R1 {
  int i_inline_size;
};

struct t_R2 {
  int i_inline_size;
  int i_reserved_quota;
};

int main() {
  struct t_R1 var_R3;
  struct t_R2 var_R4;
  if (CONFIG_QUOTA) {
    var_R4.i_reserved_quota = 1;
  }
}
