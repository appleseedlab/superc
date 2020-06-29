int main(void) {
  int x = 5;

#if A
  int myFirstArr[3];
#else
  char myFirstArr[3];
#endif

  int expressionArr[2 + 8];
  char string[2];

  int variableLength[x];

  myFirstArr[1] = 7;

  myFirstArr[x] = 3;

  return 0;
}
