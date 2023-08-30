int main() {
  int a = 0, b = 1, c = 2;
  int result;
  #ifdef ENABLE_A
  result = a ? b : c;
  #else
  if (!a)
    result = b;
  else
    result = c;
  #endif

  #ifdef ENABLE_A
  return c;
  #else
  return b;
  #endif
}
