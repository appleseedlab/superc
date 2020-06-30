// rename functions vars, factor out the common body, and create multiplexer function with original name
#ifdef A
int
#else
char
#endif
x(
#ifdef B
int y
#endif
) {
  int b = 1;
  // need to filter out invalid statements in certain presence conditions
  b = b + y;
  return b;
}

int main() {
  // create two branches, one for each call, filtering out incorrect types
  x();
  x(2);
}
