int main() {
  int a;

  #ifdef ENABLE_A
  a = 0;
  #else
  a = 1;
  #endif

  return a;
}
