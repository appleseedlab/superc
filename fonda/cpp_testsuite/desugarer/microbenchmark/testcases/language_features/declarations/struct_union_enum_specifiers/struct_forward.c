#ifdef FORWARD_SCOPE

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
#ifdef FORWARD_SCOPE
  struct s* local_var;

  struct s {
    char y;
  };
#endif
  
}
