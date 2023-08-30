#ifdef ENABLE_A

#else
struct s {
  int x;
  struct t* z;
};

struct t {
  int p;
};
#endif

int main() {
#ifdef ENABLE_A
  struct s* local_var;

  struct s {
    char y;
  };
#endif
  return sizeof(struct s);
}
