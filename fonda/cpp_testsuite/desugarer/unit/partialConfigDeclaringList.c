#ifdef A
extern int x;
#else
extern int x;
#endif
static void main()
{
  int a, b = x;
}
