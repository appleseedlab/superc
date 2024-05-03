extern int a;
#ifdef ENABLE_A
extern int a;
#endif

int main() {
  int a = 0;
  #ifdef ENABLE_A
  a++;
  #endif
  return a;
}
