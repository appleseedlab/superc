#ifdef INVALID
extern int y;
#else
#define y 1
#endif

enum bob;

int main() {
  enum bob { A = y };
}
