struct s1 {
  int data;
#ifdef GLOBAL
  struct s2 *next;
#endif
};

struct s2 {
  int data;
#ifdef GLOBAL
  struct s1 *next;
#endif
};

int main() {
  struct s3 {
    int data;
#ifdef LOCAL
    struct s4 *next;
#endif
  };

  struct s4 {
    int data;
#ifdef LOCAL
    struct s3 *next;
#endif
  };
}
