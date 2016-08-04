int main () {
  before1;
  before2;
#ifdef A
#ifdef A12
  a1;
#else
  a2;
#endif
#else
  b2;
#endif
}
