typedef 
#if A
int 
#else
char
#endif
typeAlias;

int main(void) {
  struct { typeAlias x; } intOrCharWrapper;

  intOrCharWrapper.x = 2;

  return 0;
}
