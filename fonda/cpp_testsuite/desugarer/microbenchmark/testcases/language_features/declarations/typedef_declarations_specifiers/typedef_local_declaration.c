#ifdef A
typedef int a;
#endif

int main() {
#ifdef A
  typedef a a;
  a x;
  x++;
#endif
  return 0;
}
