#ifdef A
const char x = 'c';
#else
char x = 'd';
#endif

void foo(const char c[4])
{
  #ifdef A
  int flag = c[2] == 'c';
  #else
  int flag = c[2] == 'd';
  #endif
  printf("%d\n", flag);
  return;
}

int main ()
{
  foo((char[]){'a','b',x,'d'});
  return 0;
}
