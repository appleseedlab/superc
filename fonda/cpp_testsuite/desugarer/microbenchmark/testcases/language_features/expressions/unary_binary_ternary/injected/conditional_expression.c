int main() {
  int a = 0, b = 1, c = 2;
  int result;
  #ifdef ENABLE_COND
  result = a ? b : c;
  #else
  if (!a)
    result = b;
  else
    result = c;
  #endif

  #ifdef ENABLE_COND
  int flag = result == c;
  #else
  int flag = result == b;
  #endif
  return flag;
  
}
