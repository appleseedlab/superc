struct x
{
  int a;
  #ifdef A
  int b;
  #endif
};

int main()
{
  struct x x = {1,2};
  return 0;
}
  
