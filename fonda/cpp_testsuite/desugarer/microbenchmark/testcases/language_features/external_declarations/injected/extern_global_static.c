#ifdef ENABLE_A
int f(int x) {
  return x + 1;
}
#elif defined ENABLE_B
static int f(int x) {
  return x + 2;
}
#else
extern int f(int x);
#endif

int main() {
  int x = 0;
  #ifdef ENABLE_A
  return f(x);
  #elif defined ENABLE_B
  return f(x);
  #else
  return 0;
  #endif
}
