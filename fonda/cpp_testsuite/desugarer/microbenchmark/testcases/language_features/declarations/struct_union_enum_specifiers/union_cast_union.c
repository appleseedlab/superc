#ifdef A
typedef union {
  int *a;
  long b;
} U;
#else
typedef union {
  int *a;
  long b;
} U;
#endif

#ifdef B
extern int wait(U);
#else
extern int wait(U);
#endif

void oneit_main(void)
{
  int i;
  while (wait(&i)) i;

}
