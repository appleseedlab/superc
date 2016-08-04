/* Simple asm test.  */
// {{ dg-checkwhat "c-analyzer" }}
extern int bar;

int main (void)
{
  asm ("foo %0" : "=r" (bar));
}
