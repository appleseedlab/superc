struct one {
  int a;
#ifdef ENABLE_A
  int b;
#endif
};

struct two {
#ifdef ENABLE_B
  int a;
  int b;
#else
  long long c;
  unsigned long long d;
#endif
  struct one x;
};

int main() {
  return sizeof(struct two);
}

