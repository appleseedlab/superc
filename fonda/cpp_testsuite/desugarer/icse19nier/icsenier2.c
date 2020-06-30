struct t {
  int i_inline_size;
#ifdef CONFIG_QUOTA
  int i_reserved_quota;
#endif
};

int main() {
  struct t var;
  var.i_reserved_quota = 1;
}
