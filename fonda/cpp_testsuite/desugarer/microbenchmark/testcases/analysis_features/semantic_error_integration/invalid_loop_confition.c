#ifdef A
int x;
#else
int int x;
#endif

void foo() {
  int sum = 0;
  for (int i = 0; i < x; i++)
    sum+= i;
}
