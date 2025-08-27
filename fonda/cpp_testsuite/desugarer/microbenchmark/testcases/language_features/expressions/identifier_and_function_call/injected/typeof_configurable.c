int main()
{
  typeof (
#ifdef ENABLE_A
          int *
#else
          char *
#endif
          ) x;
  typeof(x) y;
  return sizeof(*y);
}
