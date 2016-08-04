int main() {
  int i, x;
#ifdef CONFIG_A
  for (i = 0; i < 1; i++)
#else
  for (i = 0; i < 1;)
#endif
    x = 0;
}
