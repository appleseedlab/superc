int main() {
  int a, b, c;
  int result;
#ifdef COND
  result = a ? b : c;
#else
  if (a)
    result = b;
  else
    result = c;
#endif
}
