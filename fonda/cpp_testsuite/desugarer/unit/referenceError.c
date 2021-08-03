int main ()
{
  #ifdef A
  int x;
  #endif
  int y;
  y = &x;
  return 0;
}
