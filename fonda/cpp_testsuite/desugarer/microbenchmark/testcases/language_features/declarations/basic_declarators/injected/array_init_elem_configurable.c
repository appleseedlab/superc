#ifdef ENABLE_A
#define X 1
#else
#define X 2
#endif

int main() {
  int a[1] = {X};
  #ifdef ENABLE_A
  int flag = a[0] == 1;
  #else
  int flag = a[0] == 2;
  #endif
  return flag;
}
