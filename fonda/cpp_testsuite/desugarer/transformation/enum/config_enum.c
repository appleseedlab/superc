#if APPLE
enum someLetters {

  a, b, c, d, e, f
};
#else
enum someLetters {
  b, c, d, e, f
};
#endif

int main(void) {
  enum someLetters apple;
  apple = a;

  return 0;
}
