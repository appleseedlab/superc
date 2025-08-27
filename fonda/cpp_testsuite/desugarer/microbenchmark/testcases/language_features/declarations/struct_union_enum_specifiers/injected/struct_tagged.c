#ifdef ENABLE_A
struct x {
  int x;
} x;
#else
struct x {
  int x;
};
char x;
#endif

int main() {
  return sizeof(x);
}
