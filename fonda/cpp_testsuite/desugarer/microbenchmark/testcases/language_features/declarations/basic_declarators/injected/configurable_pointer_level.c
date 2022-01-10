int
#ifdef A
  *
#else
  **
#endif
    c;

int main() {
  #ifdef A
  int flag = sizeof(*c) == 4;
  #else
  int flag = sizeof(*c) == 8;
  #endif
  printf("%d\n", flag);
  
  return 0;
}
