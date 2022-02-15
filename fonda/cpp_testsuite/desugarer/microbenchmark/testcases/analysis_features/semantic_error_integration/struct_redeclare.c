struct x {
  int s;
  char t;
};

#ifdef REDECLARE
struct x {
  int y;
};
#endif

int main() {
  struct x x;
  return x.s;
}
