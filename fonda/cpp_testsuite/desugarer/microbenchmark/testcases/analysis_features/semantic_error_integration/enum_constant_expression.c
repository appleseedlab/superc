#ifdef INVALID
extern int y;
#else
#define y 1
#endif

enum bob;

enum bob x;

// type error, value is not an integer constant
enum bob { A = y };
