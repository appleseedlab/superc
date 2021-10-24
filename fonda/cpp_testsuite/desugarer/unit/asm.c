int main()
{
  int val;
  __asm__("bswapq %0" : "=r" (val) : "0" (val));
  return 0;
}
