int main() {
  #ifdef ENABLE_A
  int x[4];
  #else
  double x[5];
  #endif

  #ifdef ENABLE_A
  int flag = sizeof(x) == 16;
  #else
  int flag = sizeof(x) == 40;
  #endif
  return flag;
}