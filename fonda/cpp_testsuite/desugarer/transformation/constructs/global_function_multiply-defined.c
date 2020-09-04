// rename functions vars and create multiplexer function with original name
#ifdef A
int x() {
  return 1;
}
#else
char x() {
  return 2;
}
#endif

// need to create multiplexer function for external linkage and function pointers

int main() {
  // create two branches, one for each call
  x();
}
