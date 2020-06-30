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

int main() {
  // TODO: get pointer to function
}
