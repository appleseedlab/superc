// rename functions vars, factor out the common body, and create multiplexer function with original name
#ifdef A
int
#else
char
#endif
x() {
  return 1;
}

int main() {
  // create two branches, one for each call
  x();
}
