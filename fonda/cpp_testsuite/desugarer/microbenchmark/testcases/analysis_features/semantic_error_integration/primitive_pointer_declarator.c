int main() {
#ifdef A
  int x;
#else
  int *x;
#endif

  x = 1;
  x++;
  
  return 0;
}
