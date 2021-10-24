struct a {
  int a;
  #ifdef A
  int b;
  #endif
  int c;
};

struct b {
  int a;
  struct a field;
};

int main()
{
  struct b bee = {1,{2,3}};
  return 0;
}
