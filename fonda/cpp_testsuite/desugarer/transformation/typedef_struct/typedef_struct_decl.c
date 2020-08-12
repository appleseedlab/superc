typedef int intAlias;

int main(void) {
  struct { intAlias x; } intWrapper;

  intWrapper.x = 2;

  return 0;
}
