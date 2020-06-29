#ifdef A
typedef int a;
#endif
int main()
{
  #ifndef A
  a x;
  #endif
  return 0;
}
