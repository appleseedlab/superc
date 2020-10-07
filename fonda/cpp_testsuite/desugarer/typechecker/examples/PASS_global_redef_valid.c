#ifdef A
int x;
#endif
#ifdef B
int x;
#endif
typedef int y;
#ifdef C
y x;
#endif
int main()
{
  return -1;
}
