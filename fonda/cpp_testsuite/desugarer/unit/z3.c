#ifdef A
int x;
#else
char y;
#endif

int main() {
#ifdef A
  x = 10;
#else
  y = 'c';
#endif

#if defined(A) and defined(B)
  return 1;
#elif defined(A) or !defined(A)
  return 0;
#endif
}
