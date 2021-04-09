int main()
{
  int x =
    #ifdef A
    y;
  #else
  1;
  #endif
  int z = y;
  int a[5];
  a[x];
  a[z];
  return 0;
}
