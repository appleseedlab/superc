#ifdef ENABLE_A
int x[] = {-2, 4, 5};
#else
int y[5] = {1, 2, 3, 4, 5};
#endif

int main ()
{
  #ifdef ENABLE_A
  return sizeof(x);
  #else
  return sizeof(y);
  #endif
}
