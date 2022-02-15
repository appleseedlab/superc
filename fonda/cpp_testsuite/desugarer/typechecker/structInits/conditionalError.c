struct x {
#ifdef A
  int a;
#endif
#ifdef B
  int a;
#endif
  int b;
};

int main()
{
  struct x x = {1};
}
