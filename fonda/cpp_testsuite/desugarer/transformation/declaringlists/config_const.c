int main(void) {
  #if CONFIG_A
    int x = 2;
  #else
    char x = 3;
  #endif

  int y = x;

  return 0;
}
