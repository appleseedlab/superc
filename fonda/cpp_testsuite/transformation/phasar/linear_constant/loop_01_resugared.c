int main() {
  int x = 0;

  #ifdef CONFIG_A
    for (int i = 0; i < 10; ++i) {
      ++x;
    }
  #endif
  
  return x;
}
