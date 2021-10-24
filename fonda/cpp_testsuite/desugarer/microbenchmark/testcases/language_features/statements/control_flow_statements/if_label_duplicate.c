int main()
{
  int x;
  if (x) {
    goto lab;
  }
 lab:
  #ifdef A
  x = 1;
  #endif
  return x;
}
