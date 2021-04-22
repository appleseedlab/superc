#ifdef A
typedef int x;
#endif

int aaa;

#ifdef B
typedef int y;
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
