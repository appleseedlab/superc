#ifdef ANONYMOUS
struct {
  char p;
} data;
#endif

int main() {
#ifdef LOCAL
  struct s;
  
  struct s {
    int y;
  };
#endif
  
#ifdef ANONYMOUS
  data.p;
#endif

  return 0;
}
