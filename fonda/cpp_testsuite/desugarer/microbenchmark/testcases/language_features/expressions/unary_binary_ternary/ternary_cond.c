int x = 2;

int main ()
{
  int a;
#ifdef A
  a = x ? 0:2;
#endif
  return 0;
}
