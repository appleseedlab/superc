#ifdef CONFIG_B
int main ( ) {
  int x; 
#ifdef CONFIG_C
  int y;
#endif
  y = 4;
  x = y;
  x++;
  return x;
}
#endif
