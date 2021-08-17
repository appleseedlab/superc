#ifdef A
typedef int a;
#endif

int main() {
#ifdef B
  typedef a a;
#endif
  a x;
  x++;
  return 0;
}
