#ifdef Z
int x(int a, int b);
#else
char x(int c);
#endif
extern __typeof(x) ALIAS_x;
extern __typeof(x) ALIAS_x;

int main() {
  return sizeof(ALIAS_x);
}

