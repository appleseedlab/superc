struct s1 *x;

struct s2 {
  int data;
  struct s1 *next;
};

struct s1 {
  int data;
  struct s1 *next;
};

int main() {
#ifdef CAST
  return ((struct s2 *) x)->data;
#endif
}

