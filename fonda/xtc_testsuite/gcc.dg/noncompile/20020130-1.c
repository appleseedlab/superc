/* Test for ICE when using typedef for bad type.  */
/* Origin: Joseph Myers <jsm28@cam.ac.uk>.  */

/* {{ dg-checkwhat "c-analyzer" }} */
void
foo (void)
{
  typedef int t[x]; /* {{ dg-error "undeclared|function" }} */
  t bar;
}
