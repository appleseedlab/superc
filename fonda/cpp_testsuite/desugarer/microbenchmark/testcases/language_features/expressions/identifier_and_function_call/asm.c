int main() {
  int val;
  #ifdef ENABLE_A
  __asm__("bswap %0" : "=r" (val) : "0" (val));
  return 1;
  #else
  return 0;
  #endif
}
