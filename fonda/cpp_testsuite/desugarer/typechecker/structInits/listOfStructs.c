struct x
{
  int a;
};

int main()
{
  struct x b[10] = {{.a = 2}, {2}, [4] = {.a = 1}, {5}};
}
