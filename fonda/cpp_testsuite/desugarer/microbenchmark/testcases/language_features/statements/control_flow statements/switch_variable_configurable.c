#ifdef A
int x;
#endif

int main ()
{
  int y;
  switch (x) {
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
