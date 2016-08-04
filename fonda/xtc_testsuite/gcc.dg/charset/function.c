// {{ dg-checkwhat "c-analyzer" }}
const char *str;

void foobar (void)
{
  str = __func__;
}
