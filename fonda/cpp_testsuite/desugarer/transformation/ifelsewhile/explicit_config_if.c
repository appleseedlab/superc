int main(void) {
  int x = 2;

  if (

      #if A
        x == 2;
      #else
        x == 3;
      #endif

     ) {
    x++;
  }

  return 0;
}
 
