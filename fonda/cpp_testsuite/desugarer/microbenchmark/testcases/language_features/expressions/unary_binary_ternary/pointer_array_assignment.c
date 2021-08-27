int main()
{
#ifdef ASSIGN
  char *x[] = {"first", "second", "third"};
#else
  char *x[10];
  return 0;
}
#endif
