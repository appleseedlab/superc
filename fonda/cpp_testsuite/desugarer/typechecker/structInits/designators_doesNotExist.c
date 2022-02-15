struct x
{
  #ifdef A
  int a;
#else
  unsigned a;
#endif
};

int main()
{
  struct x x = {.a = 1, .b = 2};
  return 0;
}
