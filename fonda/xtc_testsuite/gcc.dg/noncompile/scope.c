/* {{ dg-checkwhat "c-analyzer" }} */
extern void abort (void);
extern void exit (int);
static int v = 3; /* {{ dg-error "previous definition" }} */

f ()
{
  int v = 4;
  {
    extern int v; /* {{ dg-error "'static' redeclared 'extern'" }} */   
    if (v != 3)
      abort ();
  }
}

main ()
{
  f ();
  exit (0);
}
