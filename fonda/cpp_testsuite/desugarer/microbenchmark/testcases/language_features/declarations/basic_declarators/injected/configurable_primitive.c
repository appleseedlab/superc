int main() {
#ifdef ENABLE_A
  int x;
#else
  double x;
#endif

  x = 1;
  x++;

  #ifdef ENABLE_A
  int flag = sizeof(x) == 4;
  #else
  int flag = sizeof(x) == 8;
  #endif
  return flag;
}