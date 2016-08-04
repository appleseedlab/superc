// {{ dg-checkwhat "c-analyzer" }}

void f ()
{
  int i __asm__ ("%eax");
  __asm__ volatile ("" : "=a" (i));
}


