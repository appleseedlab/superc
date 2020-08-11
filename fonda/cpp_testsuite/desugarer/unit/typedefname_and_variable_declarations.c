#ifdef A
typedef int a;
#else
int a;
#endif

int main() {
  a a;
}

int f() {
  const a a;
}
