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

#if defined(A) && defined(B)
  return 1;
#elif defined(A) || !defined(A)
  return 0;
#endif
}
