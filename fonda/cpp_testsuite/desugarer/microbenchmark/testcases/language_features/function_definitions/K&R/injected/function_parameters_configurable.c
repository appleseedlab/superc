int foo(x
      #ifdef ENABLE_A
      ,y
      #endif
      )
  char x;
  #ifdef ENABLE_A
  int y;
  #endif
{
  int ret = x;
  #ifdef ENABLE_A
  ret += y;
  #endif
  return ret;
}

int main() {
  #ifdef ENABLE_A
  return foo(1 ,2);
  #else
  return foo(1);
  #endif
}
