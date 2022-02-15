int main()
{
  typeof (
#ifdef A
          int *
#else
          char *
#endif
          ) x;
  typeof(x) y;
  y = 0;
  return 0;
}
