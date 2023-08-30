#ifdef ENABLE_A
int foo(int *);
#else
int foo (void);
int *fwo(void);
int fwotwo(void*,void*);
#endif


#ifdef ENABLE_A
int foo(int *x)
{
  return 1;
}
#else
int foo (void) { return 2; }
int *fwo(void) { int x = 1; return &x; }
int fwotwo(void*a,void*b) { return 1;}
#endif

int main() {
  int res = 0;

  #ifdef ENABLE_A
  res += sizeof(foo(&res));
  #else
  res += sizeof(foo()) + sizeof(fwo()) + sizeof(fwotwo(0, 0));
  #endif

  return res;
}
