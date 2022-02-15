#ifndef X
#define X 254
#endif
int a;
#ifndef Y
#define Y 1
#endif
int main ()
{
  switch(a) {
  case X:
    return 0;
  case Y:
    return 0;
  }
  return 1;
}
