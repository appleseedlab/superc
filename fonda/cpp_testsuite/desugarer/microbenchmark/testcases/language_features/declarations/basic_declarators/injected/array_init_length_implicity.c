#ifdef ENABLE_IMPLICIT_LENGTH
int x[] = {-2, 4, 5};
#else
int y[5] = {1, 2, 3, 4, 5};
#endif

int main ()
{
  #ifdef ENABLE_IMPLICIT_LENGTH
  int flag = sizeof(x) == 12;
  #else
  int flag = sizeof(y) == 20;
  #endif
  return flag;
}
