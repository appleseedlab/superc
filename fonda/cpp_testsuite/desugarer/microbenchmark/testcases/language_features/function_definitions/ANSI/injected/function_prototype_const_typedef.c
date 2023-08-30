#ifdef A
typedef int type;
#else
typedef long long type;
#endif
int foo (const type * x);

int main() {
  return foo(1);
}

int foo (const type * x) {
  return sizeof(x);
}
