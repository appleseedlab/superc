struct x {
  #ifdef A
  int a;
  #else
  unsigned a;
  #endif
};
struct y {
  struct x a;
  int b;
};
int main ()
{
  struct y a = {.a.a = 2};
  return 0;
}
