int main () {
  before1;
  before2;
#ifdef A
  a;
#ifdef A12
  a1;
#else
  a2;
#endif
  a_after;
#else
  b2;
#endif
  after1;
  after2;
}
