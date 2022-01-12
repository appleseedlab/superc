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
  int flag = sizeof(struct x) == 4;
  #else
  int flag = sizeof(struct x) == 12;
  #endif
  return flag;
}
