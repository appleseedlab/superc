
__attribute__ ((dllimport)) int foo;
extern int (* import) (void) __attribute__((dllimport));
int func2 (void) __attribute__((dllexport));

__attribute__ ((dllexport)) int 
func1 (int a)
{
  return a + foo;
}

static int
internal (void)
{
  return 77;
}

int
func2 (void)
{
  return import ();
}
