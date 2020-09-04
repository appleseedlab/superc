extern int A_config_C1;
extern int A_config_defined_C2;

// rename static vars, since no external linkage
#ifdef A
static int x;
#else
static char x;
#endif

int main() {
  if (A_config_defined_C2) {
    x++;
  }
  if (!A_config_defined_C2) {
    x++;
  }
}
