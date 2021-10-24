struct x {
  int a;
  int b;
  #ifdef A
  int c;
  #endif
  int d;
};

int main()
{
  struct x x = {1,2,3,.b = 4,5};
  return 0;
}
