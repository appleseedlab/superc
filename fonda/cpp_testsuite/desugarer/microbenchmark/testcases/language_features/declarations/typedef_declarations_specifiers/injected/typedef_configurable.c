typedef
#ifdef ENABLE_A
int
#else
double
#endif
a;

int main() {
  a x;
  #ifdef ENABLE_A
  int flag = sizeof(x) == 4;
  #else
  int flag = sizeof(x) == 8;
  #endif
  return flag;

}

