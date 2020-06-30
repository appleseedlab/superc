#ifdef A
typedef int a;
#endif
int main()
{
  int first;
  #ifndef A
  a x;
  #endif
  return 0;
}
