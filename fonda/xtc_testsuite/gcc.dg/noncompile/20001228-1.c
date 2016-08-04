/* {{ dg-checkwhat "c-analyzer" }} */
void rof(void)
{
  union { int a; } u;
  for (u.a = 0; u; u.a++) /* {{ dg-error "scalar required" }} */
    ;
}
