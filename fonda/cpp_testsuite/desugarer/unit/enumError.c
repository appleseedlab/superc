#ifdef A
#define X 5
#endif

enum e {
  eA = X
};

int main() {
  enum e a;
  return 0;
}
