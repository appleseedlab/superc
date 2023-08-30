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

  return sizeof(x);
}
