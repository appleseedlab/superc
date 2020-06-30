#ifdef CONFIG_B
int main() {
  #ifdef CONFIG_A
  int x;
  #else
  char x;
  #endif
  #ifdef CONFIG_C
  int y;
  #endif
  #ifdef CONFIG_D
  char y;
  #endif;

  y = 4;
  x = y;
  x++;

  return x;
}
#endif
