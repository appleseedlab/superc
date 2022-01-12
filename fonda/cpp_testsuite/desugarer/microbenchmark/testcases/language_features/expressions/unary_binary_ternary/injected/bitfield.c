struct x
{
#ifdef ENABLE_BITFIELD
  int field: 4;
#else
  long field;
#endif
};

int main() {
  struct x a,*b;
  
  #ifdef ENABLE_BITFIELD
  int flag = sizeof(a) == 4;
  #else
  int flag = sizeof(*b) == 8;
  #endif
  return flag;
}
