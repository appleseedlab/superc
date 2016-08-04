/* Test for string translation.  */
// {{ dg-checkwhat "c-analyzer" }}
void foo (void)
{
  asm ("xx" : : "r"("translate") : "cc");
}
