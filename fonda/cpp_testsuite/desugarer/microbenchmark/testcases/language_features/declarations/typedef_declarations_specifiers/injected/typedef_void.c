#ifdef ENABLE_A
typedef void v;
#else
typedef int v;
#endif
v foo(v);
v *x;

int main() {
  #ifdef ENABLE_A
  int flag = sizeof(v) == 1;
  #else
  int flag = sizeof(v) == 4;
  #endif
  return flag;
}
