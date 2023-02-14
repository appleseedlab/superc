#ifdef FORWARD
struct s {
  int x;
  struct t* z;
};
#endif

struct t {
  int p;
};

int main() {
  struct s s;
  s.z->p = 2;
  return s.z->p;
}
