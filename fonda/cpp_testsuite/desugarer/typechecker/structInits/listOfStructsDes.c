struct x
{
  int a;
};

int main()
{
  struct x b[10] = {[0].a = 2, [1]={2}, [4] = {.a = 1}, [5].a=5};
}
