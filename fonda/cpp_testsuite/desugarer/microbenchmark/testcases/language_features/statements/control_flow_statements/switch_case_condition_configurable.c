#define X 2

int main()
{
  int a;
  switch (a)
    {
#ifdef A
    case X:
      a=1;
      break;
#endif
    default:
      a=2;
    }
  return 0;
}
