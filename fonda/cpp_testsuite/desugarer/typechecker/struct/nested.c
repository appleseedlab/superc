struct inner
{
  int x;
};

struct outter
{
  struct inner a;
};

struct outter2
{
  struct inner2
  {
    int x;
  } i;
};

int main()
{
  return 0;
}
