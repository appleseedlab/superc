int main()
{
#ifdef ASSIGN
  char x[5] = "first";
#else
  char x[10];
#endif
  return 0;
}
