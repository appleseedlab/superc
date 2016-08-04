
/* Test that stray semicolon in old-style parameters is not
   accepted.  */
/* Origin: Joseph Myers <joseph@codesourcery.com> */
/* {{ dg-checkwhat "c-parser" }} */

void
f(a)
     int a;;  /* {{ dg-error "expected" }} */
{
}
