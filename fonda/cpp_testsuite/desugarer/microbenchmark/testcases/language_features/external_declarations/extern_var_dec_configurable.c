#ifdef ENABLE_A
extern int a;
#else
extern double a;
#endif

int main() {
  return sizeof(a);
}
