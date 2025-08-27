#ifdef ENABLE_A
#define __flexarr []
#endif
int a;
struct x {
  int x;
#ifdef ENABLE_A
  char name __flexarr;
#else
  char name[5];
#endif
};

int main() {
  #ifdef ENABLE_A
  return sizeof(struct x);
  #else
  return sizeof(struct x);
  #endif
}
