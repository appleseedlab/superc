int main() {
  #ifdef CONFIG_A
  int x;
  #else
  char x;
  #endif

  x++;

  return x;
}
