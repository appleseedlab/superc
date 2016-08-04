/* PR18867 - ICE on a switch controlling expressions with an
   invalid type.  Origin: Serge Belyshev <belyshev@lubercy.com>  */
/* {{ dg-checkwhat "c-analyzer" }} */   
void f()
{
  float x;
  switch (x) {case 0: break;}; /* {{ dg-error "integer required" }} */
}
