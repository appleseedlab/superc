#ifdef A
const int x = 2;
#endif

int main()
{
  int a;
  switch (a)
    {
    case x:
      a=1;
      break;
    default:
      a=2;
    }
  return 0;
}
