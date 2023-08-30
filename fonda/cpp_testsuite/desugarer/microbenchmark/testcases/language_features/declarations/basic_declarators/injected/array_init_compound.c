#ifdef ENABLE_A
const char x = 'c';
#else
char x = 'd';
#endif

int foo(const char c[4])
{
  return c[2];
}

int main ()
{
  return foo((char[]){'a','b',x,'d'});
}
