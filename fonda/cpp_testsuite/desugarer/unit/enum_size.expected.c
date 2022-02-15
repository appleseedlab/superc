extern int printf (const char *__restrict __format, ...);

enum E x;

enum E {
        A = 0x01FFFFFFFFFFFFFF,
        B,
        C,
        D = -10,
};
  
int main() {
  x = C;
  int y = x;
  printf("%016llx\n", A);
  printf("%016llx\n", B);
  printf("%016llx\n", C);
  printf("%016llx\n", x);
  printf("%016llx\n", y);
  printf("%d\n", D);
  x = D;
  printf("%016llx\n", x);
  return 0;
}
