int main()
{
#ifdef ASSIGN
  char *x[] = {"first", "second", "third"};
#else
  char *x[];
  return 0;
}
