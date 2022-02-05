int x = 1;

int main()
{
  int y;
#ifdef ENABLE_A
  y = ({x;});
#endif
  return y;
}
