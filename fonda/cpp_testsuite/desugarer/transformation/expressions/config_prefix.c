int main(void) {
  #if A
    int x;
  #else
    char x;
  #endif
  
  x = 0;

  ++x;
  --x;

  return 0;
}
