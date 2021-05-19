typedef signed int a_0;
typedef unsigned int a_1;

int foo_2(a_0 x_3)
{
  x_3++;
  return 0;
}

int foo_4(a_0 x_5)
{
  x_5++;
  return 0;
}


int main()
{
  if (A)
    foo_2(1);
  if (!A)
    foo_4(1);
  return 0;
}
