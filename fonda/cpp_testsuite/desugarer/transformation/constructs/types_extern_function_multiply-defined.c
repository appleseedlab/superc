#ifdef A
extern int x();
#else
extern float x(int);
#endif

int main() {
  x();
}
