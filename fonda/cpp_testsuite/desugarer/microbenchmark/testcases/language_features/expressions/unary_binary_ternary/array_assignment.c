int main()
{
#ifdef ASSIGN
  char x[3] = {"first", "second", "third"};
#else
  char x[10];
#endif
  return 0;
}
