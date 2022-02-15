int foo(
        int a,
#ifdef A
        float b1
#else
        float b2,
#endif
        char x
)
{return 0;}

int main()
{
  return foo(1,2,3);
}
