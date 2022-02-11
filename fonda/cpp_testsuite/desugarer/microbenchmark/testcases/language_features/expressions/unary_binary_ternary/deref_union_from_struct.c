struct x {
  int a;
  int b;
  union {
  int c;
  #ifdef ENABLE_A
    int d;
  #else
    long d;
  #endif
  };
};

int main () {
  struct x x;
  return sizeof(x);
}
