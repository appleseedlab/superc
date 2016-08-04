/* {{ dg-checkwhat "c-analyzer" }} */
main()
{
  return (struct x) {{y: 0}};   /* {{ dg-error "incomplete type" }} */
}
