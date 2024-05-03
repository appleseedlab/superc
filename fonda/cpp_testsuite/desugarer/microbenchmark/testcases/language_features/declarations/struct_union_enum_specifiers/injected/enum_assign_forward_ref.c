#ifdef ENABLE_A
enum bob;

//enum bob x;

enum bob { A };
#endif

#ifdef ENABLE_B
//enum E y;

enum E {
        B = 0x01FFFFFFFFFFFFFF,
        C,
        D,
        E = -10,
};
#endif

int main() {
  int size1 = 1;
#ifdef ENABLE_A
  size1 = sizeof(enum bob);
#endif

  int size2 = 2;
#ifdef ENABLE_B
  size2 = sizeof(enum E);
#endif

  return size1 + size2;


}
