// {{ dg-checkwhat "c-analyzer" }}

float foo(unsigned char n)
{
  float r = 10 * n;
  asm volatile("" : : : "memory");
  return r;
}
