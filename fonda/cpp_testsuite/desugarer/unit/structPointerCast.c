struct x {
  int a;
  int b;
  int c;
};

const struct x* var;

int main()
{
  (*(struct x**)&var) = (void*)0;
  return 0;
}
