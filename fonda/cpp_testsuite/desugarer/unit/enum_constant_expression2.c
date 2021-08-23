#ifdef A
int y = 7;
#else
const int y = 7;
#endif
enum bob;

enum bob x;

// type error: value for A is not an integer constant
enum bob { A = y + 2 };
