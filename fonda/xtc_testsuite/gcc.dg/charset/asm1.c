// {{ dg-checkwhat "c-analyzer" }}
extern int x, y;

asm (".ascii bar");

int foo (void)
{
  __asm__ (".ascii foo");
  return 0;
}
