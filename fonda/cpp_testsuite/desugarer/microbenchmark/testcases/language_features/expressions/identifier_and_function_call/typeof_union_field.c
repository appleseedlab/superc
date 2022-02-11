int main()
{
  #ifdef ENABLE_A
  int *x;
  #else
  int x;
  #endif
  union {
    typeof(x) a;
    int b;
  } y;
  return sizeof(y);
}
