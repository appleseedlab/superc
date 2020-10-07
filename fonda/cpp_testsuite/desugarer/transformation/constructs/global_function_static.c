#ifdef A
static int x() {
  return 1;
}
#else
static char x() {
  return 2;
}
#endif

int main() {
  x();
}
