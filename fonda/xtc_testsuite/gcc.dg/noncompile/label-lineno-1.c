/* Ensure that diagnostics for labels appear on the correct lineno.
   by Kaveh R. Ghazi <ghazi@caip.rutgers.edu> 8/23/2000.  */
/* {{ dg-checkwhat "c-analyzer" }} */
void
foo(int i)
{
 my_label: /* {{ dg-error "previous definition" }} */

  i++;

 my_label: /* {{ dg-error "duplicate label" }} */

  i++;
}
