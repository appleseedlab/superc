int main ()
{
  int y;
#ifdef A
  int x;
#else
  int z;
#endif

#ifdef A
  switch (x) {
#else
  switch (z) {
#endif
  case 1:
    y = 2;
    break;
  case 2:
    y = 3;
    break;
  default:
    y = 0;
  }
  return y;
}
