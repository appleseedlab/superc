#ifdef CONFIG_B
int main() {
  #ifdef CONFIG_A
  int x;
  #endif

  x = 2;
  x++;

  return x;
}
#endif
