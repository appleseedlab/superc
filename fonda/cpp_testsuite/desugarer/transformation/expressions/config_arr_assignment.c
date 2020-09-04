int main(void) {
  int x = 2;
  int arr[5];

#if A
  arr[1] = 7;
#else
  arr[x] = 3;
#endif

  return 0;
}
