/* PR c/18946 */

/* {{ dg-checkwhat "c-analyzer" }} */
void bar (void)
{
  {
    if (foo)		/* {{ dg-error "undeclared" }} */
      foo ();
  }
}

void baz (void)
{
  if (foo)		/* {{ dg-error "undeclared" }} */
    {
      int foo;
    }
}
