#ifdef A
extern int x();
#else
extern float x();
#endif

int main() {
  x();
}
