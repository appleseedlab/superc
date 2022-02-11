#ifdef ENABLE_A
int x;
#else
char x;
#endif

int main() {
  #ifdef ENABLE_A
  double x;
  #endif
  x++;

  return sizeof(x);
}
