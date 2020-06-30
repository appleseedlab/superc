#ifdef A
float f() {
  return 0;
}
#else
extern int f;
#endif

int main() {
  #ifdef A
  f();
  #else
  f;
  #endif
  return 0;
}
