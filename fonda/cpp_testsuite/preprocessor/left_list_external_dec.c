#ifdef X
#define foo(x) do {} while (0)
#else
void foo(int x) {
}
#endif
int main() {
  foo(x);
  x;
}
