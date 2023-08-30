#ifdef ENABLE_A
int f(int **(x)[4][5])
#else
int f(int (**(x)[5][6]))
#endif

{
  return sizeof(*x);
}

int main() {
  return f(0);
}

