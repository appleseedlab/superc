extern int y;

enum bob;

enum bob x;

// type error, value is not an integer constant
enum bob { A = y };
