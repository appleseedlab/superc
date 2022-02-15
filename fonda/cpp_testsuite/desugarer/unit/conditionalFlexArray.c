#ifdef A
typedef int x;
#else
typedef short x;
#endif

int a;
struct s {
  int data;
  x id[];
};

int main()
{
  return 0;
}
