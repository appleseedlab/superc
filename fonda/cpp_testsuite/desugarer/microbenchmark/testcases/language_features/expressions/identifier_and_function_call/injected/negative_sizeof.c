struct X {
  int a;
  int b;
  int c;
};

struct Y {
#ifdef ENABLE_A
  int a;
  int b;
#else
  long a;
  long b;
#endif
} y;

int main()
{
  int res = (int) sizeof(struct X) - (int) sizeof(y);
  return res;
}
