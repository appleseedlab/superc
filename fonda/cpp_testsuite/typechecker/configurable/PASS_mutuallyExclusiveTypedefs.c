typedef
#ifdef A
int
#else
float
#endif
a;
int main()
{
  a x;
  #ifdef A
  a
    #else
    int
    #endif
    y;
  #ifndef A
  a z;
  #endif
  #ifdef B
  a
    #else
    char
    #endif
    w;
  return 0;
  
}
