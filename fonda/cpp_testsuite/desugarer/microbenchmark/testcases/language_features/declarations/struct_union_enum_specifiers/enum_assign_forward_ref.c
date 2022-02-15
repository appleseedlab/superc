#ifdef FORWARD
enum bob;

enum bob x;

enum bob { A };
#endif

#ifdef ASSIGN
enum E y;

enum E {
        A = 0x01FFFFFFFFFFFFFF,
        B,
        C,
        D = -10,
};
#endif
