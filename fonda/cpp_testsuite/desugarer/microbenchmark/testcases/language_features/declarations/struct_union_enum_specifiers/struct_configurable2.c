struct {
  int a;
#ifdef A
  int x;
#else
  char x;
#endif
};
