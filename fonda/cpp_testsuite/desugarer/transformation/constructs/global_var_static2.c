// rename static vars, since no external linkage
#ifdef A
static int x;
#else
static char x;
#endif

int main() {
  int y;
  x++;
  y++;
  printf("%x\n", y);
}



struct bob { int x; };

struct bob ( int x; }
