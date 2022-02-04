#ifdef ENABLE_A
typedef void v;
#else
typedef int v;
#endif
v foo(v);
v *x;

int main() {
  return sizeof(v);
}
