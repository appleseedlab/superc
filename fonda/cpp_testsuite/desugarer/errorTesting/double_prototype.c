#ifdef A
int foo()
#endif
#ifdef B
  int bar()
#endif
{
  return 1;
}

int main()
{
  return 0;
}
