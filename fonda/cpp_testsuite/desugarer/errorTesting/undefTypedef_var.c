#ifdef A
typedef int x;
#endif

int main()
{
  #ifdef A
  x a;
  #else
  x b;
  #endif
  return 0;
}
