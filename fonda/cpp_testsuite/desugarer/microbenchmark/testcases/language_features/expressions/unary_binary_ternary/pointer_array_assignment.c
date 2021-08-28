int main()
{
#ifdef ASSIGN
  char x[] = {"first", "second", "third"};
#else
  char x[10];
#endif
  return 0;
}
