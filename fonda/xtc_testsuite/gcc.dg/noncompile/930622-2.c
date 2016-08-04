/* {{ dg-checkwhat "c-parser" }} */
f ()
{
  int i;
  for (i--)	 /* {{ dg-error "expected" }} */
    ;
}
