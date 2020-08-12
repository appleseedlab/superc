#if A
union intCharFloat {
  int integer;
  char character;
  float floating;
};
#else
union intCharFloat {
  int integer;
};
#endif

int main(void) {
  union intCharFloat usedUnion;

  usedUnion.integer = 1;

  usedUnion.char = 'h';

  return 0;
}