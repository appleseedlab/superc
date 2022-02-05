struct x
{
#ifdef ENABLE_A
  int field: 4;
#else
  long field;
#endif
};

int main() {
  struct x a,*b;
  
  #ifdef ENABLE_A
  return sizeof(a);
  #else
  return sizeof(*b);
  #endif
}
