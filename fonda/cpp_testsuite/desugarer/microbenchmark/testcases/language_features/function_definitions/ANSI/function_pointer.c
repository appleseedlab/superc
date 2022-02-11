#ifdef ENABLE_A
int foo(int x) {return 1;}

int (*fun_ptr)(int) = &foo;
#endif

int main() {
#ifdef ENABLE_A
  return fun_ptr(0);
#else
  return 0;
#endif

}
