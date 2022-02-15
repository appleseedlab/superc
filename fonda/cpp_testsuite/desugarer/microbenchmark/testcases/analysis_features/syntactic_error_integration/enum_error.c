#ifdef REPEATED
enum E {
        A, B, A,
};
#else
enum E {
      A = 11,
      B = 11,
};
#endif

int main() {
  enum E e = A;
  return 0;  
}
