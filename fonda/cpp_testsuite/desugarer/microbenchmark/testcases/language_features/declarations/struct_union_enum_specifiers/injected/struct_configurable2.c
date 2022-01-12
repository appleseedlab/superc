struct {
  int a;
#ifdef ENABLE_A
  int x;
#else
  double x;
#endif
} a;

int main() {
  #ifdef ENABLE_A
  int flag = sizeof(a) == 8;
  #else
  int flag = sizeof(a) == 16;
  #endif
  return flag;
}
