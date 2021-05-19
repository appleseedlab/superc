typedef struct x
{
  int a;
  int b;
} X;

int main()
{
  X a;
  {
    a.a = 1;
    a.b = 2;
  }
  return 0;
}
