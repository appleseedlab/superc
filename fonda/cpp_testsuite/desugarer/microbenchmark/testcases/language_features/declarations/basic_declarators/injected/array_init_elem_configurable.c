#ifdef ENABLE_A
#define X 1
#else
#define X 2
#endif

int main() {
  int a[1] = {X};
  return a[0];
}

