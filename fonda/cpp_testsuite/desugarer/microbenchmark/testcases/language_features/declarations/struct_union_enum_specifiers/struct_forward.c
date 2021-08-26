#ifdef FORWARD_SCOPE
int main() {
  struct s* local_var;

  struct s {
    char y;
  };

  return local_var->y;
}

struct s {
  int x;
};
#else
struct s {
  int x;
  struct t* z;
};

struct t {
  int p;
};
#endif
