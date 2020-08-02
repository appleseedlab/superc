#ifdef A
typedef int z;
#else
typedef float z;
#endif

struct x
{
  z a;
};

int main()
{
  return 0;
}
