#ifdef A
typedef int a;
#endif
#ifdef B
typedef char a;
#endif
#ifdef C
typedef char char a;
#endif

int main() {
  const a a;
}
