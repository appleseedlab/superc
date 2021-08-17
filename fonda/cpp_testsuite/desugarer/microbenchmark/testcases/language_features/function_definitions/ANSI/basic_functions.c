#ifdef BASIC_FUNC
int x()
{
  return 0;
}

float *y(int y1)
{
  float* y2;
  return y2; 
}

char z(int z1, int z2)
{
  return 'a';
}

short w(int x, ...)
{
  return 0;
}
#endif

#ifdef VALID_TYPE_FUNC
void * a;
void b()
{
  return;
}

inline int c()
{
  return 0;
}
#endif
