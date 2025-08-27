int x
#ifdef A
() { return 2;}
#endif
  ;

int main()
{
  char a;
  a = (char) x();
  return a;
}
