int main() {
#ifdef ENABLE_A
  int x;
#else
  double x;
#endif

  x = 1;
  x++;

  return sizeof(x);
}
