int main()
{
  int x = 2;
  if (x) {
    goto lab;
  }
 lab:
  #ifdef ENABLE_A
  x = 1;
  #endif
  return x;
}
