unsigned long long                                /* {{ dg-warning "return type" }} */
main ()
{
  return (unsigned long long) 7816234 << 671111;  /* {{ dg-warning "left shift count" }} */
}
