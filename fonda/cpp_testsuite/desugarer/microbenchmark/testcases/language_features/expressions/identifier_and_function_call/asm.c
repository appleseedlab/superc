int main()
{
  int val;
#ifdef ASM
  __asm__("bswapq %0" : "=r" (val) : "0" (val));
#endif
  return 0;
}
