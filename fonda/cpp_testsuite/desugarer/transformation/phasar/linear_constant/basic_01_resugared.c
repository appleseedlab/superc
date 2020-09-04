int main() {
  int x;

  #ifdef CONFIG_A
    x = 42;
  #else
    x = 13;
  #endif

  return x;
}
