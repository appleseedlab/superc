int main() {
  int a;

  #ifdef ENABLE_A
  a = 0;
  #else
  a = 1;
  #endif

  #ifdef ENABLE_A
  int flag = a == 0;
  #else
  int flag = a == 1;
  #endif
  return flag;
}
