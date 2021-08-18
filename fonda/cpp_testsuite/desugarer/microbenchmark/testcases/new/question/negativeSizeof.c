struct X {
  int a;
  int b;
  int c;
};

struct Y {
#ifdef A
  int a;
  int b;
#else
  int a;
  int b;
#endif
} y;

int main()
{
  int a[sizeof(struct X) - sizeof y];
  return 0;
}
