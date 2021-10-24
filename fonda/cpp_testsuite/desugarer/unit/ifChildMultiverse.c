int main()
{
  #ifdef A
  int x;
  #else
  char x;
  #endif
  x = 2;
  int y;
  if (y) x++;
  return 0;
}
