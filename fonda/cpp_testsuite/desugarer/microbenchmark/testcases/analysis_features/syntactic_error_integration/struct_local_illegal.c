int main() {
#ifdef ILLEGAL
  struct s x;
#endif

  struct s {
    int y;
  };
}
