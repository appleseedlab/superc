int main ()
{
  int y;
#ifdef ENABLE_A
  int x = 1;
#else
  int z = 2;
#endif

#ifdef ENABLE_A
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
