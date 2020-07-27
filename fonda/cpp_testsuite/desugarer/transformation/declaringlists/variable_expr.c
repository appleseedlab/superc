int main(void) {

  #if CONFIG_A
  int x = 2;
  int y = 3;
  #else
  char x = 4;
  int y = 5;
  #endif

 

  int z = x + y;

  return 0;
}