#ifdef A
#define SIZE 255
#endif
struct x {
  int a;
  int b[SIZE];
  int c;
};

const struct x* var;

int main()
{
  (*(struct x**)&var) = (void*)0;
  return 0;
}
