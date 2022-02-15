int y = 7;

enum bob;

enum bob x;

// type error: value for A is not an integer constant
enum bob { A = y + 2 };
