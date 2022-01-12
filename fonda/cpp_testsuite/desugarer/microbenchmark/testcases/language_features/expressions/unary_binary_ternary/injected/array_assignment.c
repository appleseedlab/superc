int main()
{
#ifdef ENABLE_ASSIGN
  char x[5] = "first";
#else
  char x[10];
#endif

#ifdef ENABLE_ASSIGN
  int flag = sizeof(x) == 5;
#else
  int flag = sizeof(x) == 10;
#endif
  return flag;
}
