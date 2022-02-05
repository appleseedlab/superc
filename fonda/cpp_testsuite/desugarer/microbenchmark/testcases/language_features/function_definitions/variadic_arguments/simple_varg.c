#ifdef A
int foo (int a, ...)
#else
int foo (int a, int b, int c, int d)
#endif
{
  
}

int main () {
  foo (1, 2, 3, 4);
}
