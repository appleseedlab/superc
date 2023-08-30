int main()
{
  int x = 2;
  switch (x) {
  case 1:
    x = 2;
    break;
  #ifdef ENABLE_A
  case 2:
    x = 3;
    break;
  #else
  case 2:
    x = 4;
    break;
  #endif
    default:
    x = 0;
  }
  return x;
}
