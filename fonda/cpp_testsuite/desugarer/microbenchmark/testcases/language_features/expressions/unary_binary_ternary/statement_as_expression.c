int x;

int main()
{
  int y;
#ifdef A
  y = ({x;});
#endif
  return 0;
}
