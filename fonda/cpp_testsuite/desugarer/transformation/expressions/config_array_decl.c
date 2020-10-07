int main(void) {
  int x = 5;

#if A
  int arr[3];
#else
  char arr[2 + x];
#endif

  return 0;
}
