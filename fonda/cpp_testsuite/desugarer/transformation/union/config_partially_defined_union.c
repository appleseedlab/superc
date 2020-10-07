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

  usedUnion.character = 'h';

  return 0;
}
