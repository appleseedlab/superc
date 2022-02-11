#ifdef ENABLE_A
int x = 1;
#else
long x = 2;
#endif
int main() {
  int a = 1, b = x;

  return a + b;
  
}
