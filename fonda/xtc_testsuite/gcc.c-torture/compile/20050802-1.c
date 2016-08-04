/* PR 23196 */


void foo()
{
  char c;

  c |= 1;
  bar(&c);
}
