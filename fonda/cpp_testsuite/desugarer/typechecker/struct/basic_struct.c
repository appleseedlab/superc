struct basic
{
  int x;
};

struct basic2
{
  int a;
  int b;
};

struct basic3
{
  int i;
  char j;
  float k;
};

struct nested
{
  struct basic a;
  struct basic2 b;
  struct basic3 c;
};

int main()
{
  return 0;
}
