#ifdef A
typedef int AX;
#endif
int main ()
{
  int x = 5 + sizeof(AX);
  return x;
}
