#ifdef A
const char x = 'c';
#else
char x = 'c';
#endif

void foo(const char c[4])
{
  return;
}

int main ()
{
  foo((char[]){'a','b',x,'d'});
  return 0;
}
