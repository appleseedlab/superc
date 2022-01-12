#ifdef ENABLE_A
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
  #ifdef ENABLE_A
  int flag = sizeof(a) == 4;
  #else
  int flag = sizeof(a) == 8;
  #endif
  return flag;
}
