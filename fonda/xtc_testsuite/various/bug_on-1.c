// {{ dg-preprocess "Need preprocessing" }}

#define bug_on(condition) ((void)sizeof(char[1 - 2*!!(condition)]))

#define offset(type, member) ((unsigned int)(&((type *)0)->member))

struct s {
  char b;
  char c;
};

int main(void) {
  bug_on(0);
  bug_on(1); // {{ dg-error "size of array is negative" }}
  bug_on(1 != offset(struct s, c));
  bug_on(1 == offset(struct s, c)); // {{ dg-error "size of array is negative" }}
}
