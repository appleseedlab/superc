#ifdef CONFIG_A
struct {
  int a;
#ifdef CONFIG_B
  int x;
#endif
#ifdef CONFIG_C
  int yy;
#endif
};
#endif

int main() {
  return 0;
}
