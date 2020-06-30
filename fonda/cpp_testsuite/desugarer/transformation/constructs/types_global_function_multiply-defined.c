// rename functions vars and create multiplexer function with original name
#ifdef A
int x() {
  return 1;
}
#else
char x(int y) {
  return y;
}
#endif

// need to create multiplexer function for external linkage and function pointers

int main() {
  // need to trim type errors
  x();
  x(2);
}
