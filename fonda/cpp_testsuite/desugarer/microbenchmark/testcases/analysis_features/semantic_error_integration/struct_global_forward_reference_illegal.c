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
  return s.z->p;
}
