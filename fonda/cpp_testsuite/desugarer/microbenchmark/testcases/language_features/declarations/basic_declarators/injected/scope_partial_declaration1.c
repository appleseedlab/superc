#ifdef ENABLE_A
int x;
#else
char x;
#endif

int main() {
  #ifdef ENABLE_B
  double x;
  #endif
  x++;

  return sizeof(x);
}
