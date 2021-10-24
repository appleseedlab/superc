const int x = 2;

int main()
{
  int a;
  switch (a)
    {
#ifdef A
    case x:
      a=1;
      break;
#endif
    default:
      a=2;
    }
  return 0;
}
