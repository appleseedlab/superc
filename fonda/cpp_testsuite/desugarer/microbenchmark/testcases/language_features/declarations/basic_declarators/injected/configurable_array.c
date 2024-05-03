int main() {
  #ifdef ENABLE_A
  int x[4];
  #else
  double x[5];
  #endif

  return sizeof(x);
}
