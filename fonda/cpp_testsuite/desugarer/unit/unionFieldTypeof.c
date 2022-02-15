int main()
{
  #ifdef A
  int *x;
  #else
  long x;
  #endif
  union {
    typeof(x) a;
    int b;
  } y;
  return 0;
}
