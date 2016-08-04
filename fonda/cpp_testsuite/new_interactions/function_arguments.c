#ifdef A
#define F(x, y, z) printf("function-like: " x, y, z);
#elif defined B
#define F(x, var...) printf("function-like variadic: " x, ## var);
#elif defined C
#define F printf("object-like: "); printf
#else
int F(char *s, int x, int y) {
  printf("C function: ");
  printf(s, x, y);
}
#endif

int main() {
  F("%d %d", 1, 2);
  printf("\n");
}
