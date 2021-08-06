#define __flexarr []
int a;
struct x {
  int x;
  char name __flexarr;
};

int main(){
  a = sizeof(struct x);
  return a;
}
