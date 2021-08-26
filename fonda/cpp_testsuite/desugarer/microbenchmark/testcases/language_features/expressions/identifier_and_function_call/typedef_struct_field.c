#ifdef A
typedef int s;
#else
typedef long s;
#endif

struct x {
  int data;
  s id[];
};

int main()
{
  struct x a;
  return 0;
}
