#ifdef ENABLE_A
int foo(int *);
#else
void foo (void);
void *fwo(void);
void fwotwo(void*,void*);
#endif


#ifdef ENABLE_A
int foo(int *x)
{
  return 1;
}
#endif

int main() {
  int res = 0;

  #ifdef ENABLE_A
  res += sizeof(foo(0));
  #else
  res += sizeof(foo()) + sizeof(fwo()) + sizeof(fwotwo(0, 0));
  #endif

  return res;
}
