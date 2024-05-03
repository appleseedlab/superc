int main() {
  int x = 0;
  while (++x < 5) {
#ifdef ENABLE_A
    break;
#endif
#ifdef ENABLE_B
    continue;
#endif
    goto ret;
  }
  return x;
ret:
  return 6;
}
