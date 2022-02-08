struct s1 {
  int data;
#ifdef ENABLE_A
  struct s2 *next;
#endif
};

struct s2 {
  int data;
#ifdef ENABLE_A
  struct s1 *next;
#endif
};

int main() {
  struct s3 {
    long data;
#ifdef ENABLE_A

#else
    struct s4 *next;
#endif
  };

  struct s4 {
    long data;
#ifdef ENABLE_A

#else
    struct s3 *next;
#endif
  };

  return sizeof(struct s1) + sizeof(struct s2) + sizeof(struct s3) + sizeof(struct s4);
}
