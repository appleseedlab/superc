#ifdef A
#define X 1
#else
#define X 2
#endif

int main() {
  int a[1] = {X};
  #ifdef A
  int flag = a[0] == 1;
  #else
  int flag = a[0] == 2;
  #endif
  printf("%d\n", flag);
  return 0;
}

