/* Test for attribute non-translation.  */
// {{ dg-checkwhat "c-analyzer" }}

int walrus __attribute__ ((section (".foo")));

int main (void)
{
  return 0;
}
