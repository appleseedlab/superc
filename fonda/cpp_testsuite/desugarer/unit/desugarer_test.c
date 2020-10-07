struct s {
  union {
    struct {
      int x;
    } s1;
    struct {
      char x;
    } s2;
    struct {
      char y;
    } s3;
  };
};

int main() {
  struct s t;
  t.s1.x = 1;
  t.s3.y = 2;
}
