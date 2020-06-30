int increment(int i) { return ++i; }

int main() {
  int x = 99;
  
  #ifdef CONFIG_A
    x = increment(x);
  #endif

  return x;
}
