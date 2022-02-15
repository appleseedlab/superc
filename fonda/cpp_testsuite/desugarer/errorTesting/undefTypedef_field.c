#ifdef A
typedef int x;
#endif

struct x{
    #ifdef A
  x a;
  #else
  x b;
  #endif
};

int main()
{
  struct x c;
  return 0;
}
