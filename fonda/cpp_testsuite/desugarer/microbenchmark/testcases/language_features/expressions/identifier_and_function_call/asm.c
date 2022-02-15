int main()
{
  int val;
#ifdef ASM
  __asm__("bswap %0" : "=r" (val) : "0" (val));
#endif
  return 0;
}
