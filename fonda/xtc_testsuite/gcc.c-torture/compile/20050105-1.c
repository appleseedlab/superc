void bar (struct S *); // {{ dg-warning "inside parameter list" }}
void foo (void *x)
{
  bar ((struct S *) x); // {{ dg-warning "incompatible pointer types" }}
}
