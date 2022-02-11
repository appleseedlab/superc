struct {
  int a;
#ifdef ENABLE_A
  int x;
#else
  double x;
#endif
} a;

int main() {
  return sizeof(a);
}
