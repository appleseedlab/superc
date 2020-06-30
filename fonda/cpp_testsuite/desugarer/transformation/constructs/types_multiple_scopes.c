// differing scopes really don't matter unless the types are not both the same class (primitive, struct, etc)

#ifdef A
static int x;
#endif

int main() {
#ifndef A
  char x;
#endif

  x++;

  return x;
}

