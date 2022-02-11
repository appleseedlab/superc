int main()
{
#ifdef ENABLE_A
  char x[5] = "first";
#else
  char x[10];
#endif

  return sizeof(x);
}
