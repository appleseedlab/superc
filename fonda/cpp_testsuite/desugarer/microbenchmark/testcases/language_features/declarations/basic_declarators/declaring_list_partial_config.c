#ifdef A
extern int x;
#else
extern long x;
#endif
int main() {
  int a, b = x;
}
