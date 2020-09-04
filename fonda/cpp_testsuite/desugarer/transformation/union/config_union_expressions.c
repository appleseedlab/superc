#if A
union intCharFloat {
  int integer;
  char character;
  float floating;
};
#else
union intCharFloat {
  char integer;
};
#endif

int main(void) {
  union intCharFloat usedUnion;

  usedUnion.integer = 1;
  usedUnion.character = 'h';

  int x = usedUnion.integer;

  int y;

  y = usedUnion.integer + usedUnion.character;

  #if B
  usedUnion.integer++;
  #endif

  #ifdef C
  int z = usedUnion.integer % usedUnion.character;
  #else
  char ch = usedUnion.character;
  #endif

  return 0;
}