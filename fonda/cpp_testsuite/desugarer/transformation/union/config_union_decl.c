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

  return 0;
}