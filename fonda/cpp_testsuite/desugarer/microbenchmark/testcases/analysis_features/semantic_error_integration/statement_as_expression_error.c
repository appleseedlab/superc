#ifdef A
int x;
#endif

int main()
{
  int y;
  y = ({x;});
  return 0;
}
