int main() {
  int x =
#ifdef A
    1
#else
    2
#endif
    ;
}
