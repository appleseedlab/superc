// rename static vars, since no external linkage
#ifdef A
static int x;
#else
static char x;
#endif

int main() {
  x++;
}
