#ifdef ENABLE_NAMESPACE
struct x {
  int x;
} x;
#else
struct x {
  int x;
};
char x;
#endif

int main() {
  #ifdef ENABLE_NAMESPACE
  int flag = sizeof(x) == 4;
  #else
  int flag = sizeof(x) == 1;
  #endif
  return flag;
}
