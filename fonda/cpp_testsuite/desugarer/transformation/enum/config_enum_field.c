enum someLetters {
  #if APPLE
  a, 
  #endif
  b, c, d, e, f
};

int main(void) {
  enum letter apple;
  apple = a;

  return 0;
}