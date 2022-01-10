#ifdef FORWARD
enum bob;

enum bob x;

enum bob { A };
#endif

#ifdef ASSIGN
enum E y;

enum E {
        B = 0x01FFFFFFFFFFFFFF,
        C,
        D,
        E = -10,
};
#endif

int main() {
#ifdef FORWARD
  int flag1 = sizeof(enum bob) == 4;
#else
  int flag1 = 1;
#endif

#ifdef ASSIGN
  int flag2 = sizeof(enum E) == 8;
#else
  int flag2 = 1;
#endif

  int flag = flag1 && flag2;
  printf("%d\n", flag);


}
