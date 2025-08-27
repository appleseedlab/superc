int x = 1;

int main()
{
  int y = 0;
#ifdef ENABLE_A
  y = ({x;});
#endif
  return y;
}
