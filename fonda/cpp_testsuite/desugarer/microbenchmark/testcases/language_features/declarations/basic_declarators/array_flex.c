#ifdef A
#define __flexarr []
#endif
int a;
struct x {
  int x;
#ifdef A
  char name __flexarr;
#endif
};

int main(){
  a = sizeof(struct x);
  return a;
}
