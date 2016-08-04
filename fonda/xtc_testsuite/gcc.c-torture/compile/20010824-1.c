void f(int n)
{
bugcauser: // {{ dg-warning "defined but not used" }}
  if (n != 0)
    f(n-1);
  return;
}
