#if A
union intCharFloat {
  int integer;
  char character;
  float floating;
};
#endif

int main(void) {
  union intCharFloat usedUnion;

  usedUnion.integer = 1;

  usedUnion.char = 'h';

  return 0;
}