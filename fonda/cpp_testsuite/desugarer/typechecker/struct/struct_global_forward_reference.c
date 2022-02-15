struct s;

struct t;

struct s {
  int x;
  struct t y;
  struct t* z;
};

struct t {
  int p;
};
