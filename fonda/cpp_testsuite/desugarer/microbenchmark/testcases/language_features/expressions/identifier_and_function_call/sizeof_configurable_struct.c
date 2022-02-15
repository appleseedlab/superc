typedef int a;
int x;

struct one
{
  a a;
#ifdef A
  int b;
#endif
};

struct two
{
#ifdef B
  int a;
  int b;
#else
  long long c;
  unsigned long long d;
#endif
  struct one x;
};

int main()
{
  int z;
  z = sizeof(struct two);
  return z;
}

