#ifdef ENABLE_A
typedef int a;
#endif

int main() {
  #ifdef ENABLE_A
  typedef a a;
  a x;
  #else
  long x;  
  #endif

  x++;

  #ifdef ENABLE_A
  int flag = sizeof(x) == 4;
  #else
  int flag = sizeof(x) == 8;
  #endif
  return flag;
}
