/* Test for segfault doing -Wsequence-point processing on an empty
   statement expression.  */
/* Origin: PR c/3259 from <David.Decotigny@irisa.fr>.  */
// {{ dg-checkwhat "c-analyzer" }}

void
f (void)
{
  ({ });
}
