struct {
  int a;
#ifdef ENABLE_A
  int x;
#endif
#ifdef ENABLE_B
  int y;
#endif
} a;

int main() {
  return sizeof(a);
}
