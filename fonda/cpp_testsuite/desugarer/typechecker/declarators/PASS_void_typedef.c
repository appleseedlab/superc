typedef void v;

v foo(v); //valid

v x; //invalid

int main()
{
  return 0;
}

v foo(v)
{
  return;
}
