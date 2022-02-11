#ifdef ENABLE_A
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

#ifdef ENABLE_B
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

int main(){
  int res = 0;
  #ifdef ENABLE_A
    res += sizeof(x()) + sizeof(y(0)) + sizeof(z(1, 2)) + sizeof(w(0, 1, 2, 3));
  #endif

  #ifdef ENABLE_B
    res += sizeof(a) + sizeof(b()) + sizeof(c());
  #endif

  return res;
}
