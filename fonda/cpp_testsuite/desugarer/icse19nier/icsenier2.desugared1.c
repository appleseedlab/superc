bool CONFIG_QUOTA; /* originally a macro */

struct t {
  int i_inline_size;
  int i_reserved_quota;
};

int main() {
  struct t var;
  if (CONFIG_QUOTA) {
    var.i_reserved_quota = 1;
  }
}
