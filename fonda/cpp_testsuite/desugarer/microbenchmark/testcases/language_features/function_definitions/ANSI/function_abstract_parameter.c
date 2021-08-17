#ifdef ABSTRACT_PARAM
int foo(int *);
#endif

#ifdef VOID_ABSTRACT
void foo (void);
void *fwo(void, void);
void fwotwo(void*,void*);
#endif


#ifdef ABSTRACT_PARAM
int foo(int *x)
{
  return 1;
}
#endif
