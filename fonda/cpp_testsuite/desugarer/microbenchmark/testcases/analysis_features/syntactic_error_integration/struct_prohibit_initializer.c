struct bob {
#ifdef INIT
  int x = 1;
#else
  int x;
#endif
} globalvar;

int main() {
  struct bob bobvar;
}
