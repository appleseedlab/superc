
union intCharFloat {
  int integer;
  #if A
  char character;
  #endif
  float floating;
};

int main(void) {
  union intCharFloat usedUnion;

  usedUnion.integer = 1;

  usedUnion.character = 'h';

  return 0;
}
