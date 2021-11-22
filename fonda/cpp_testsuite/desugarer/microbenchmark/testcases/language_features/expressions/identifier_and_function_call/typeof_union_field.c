int main()
{
  #ifdef A
  int x;
  #else
  long long  x;
  #endif
  union {
    typeof(x) a;
    int b;
  } y;
  return sizeof(y);
}
