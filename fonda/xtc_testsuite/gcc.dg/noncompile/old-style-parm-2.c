/* Test that parameter without declaration specifiers in old-style
   parameters is not accepted.  */
/* Origin: Joseph Myers <joseph@codesourcery.com> */
/* {{ dg-checkwhat "c-parser" }} */

void
f(a)
     a; /*  {{ dg-error "expected" }} */
{
}
