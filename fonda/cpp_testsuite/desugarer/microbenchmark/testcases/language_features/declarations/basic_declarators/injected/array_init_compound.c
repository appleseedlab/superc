#ifdef ENABLE_A
const char x = 'c';
#else
char x = 'd';
#endif

int foo(const char c[4])
{
  #ifdef ENABLE_A
  int flag = c[2] == 'c';
  #else
  int flag = c[2] == 'd';
  #endif
  return flag;
}

int main ()
{
  return foo((char[]){'a','b',x,'d'});
}
