#define X 2

int main()
{
  int a = 2;
  switch (a)
    {
#ifdef ENABLE_A
    case X:
      a=1;
      break;
#endif
    default:
      a=2;
    }
  return a;
}
