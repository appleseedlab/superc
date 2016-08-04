int main() {
  int x =
#ifdef A
    1;
  int y
#else
    2;
  int z
#endif
    ;
}
