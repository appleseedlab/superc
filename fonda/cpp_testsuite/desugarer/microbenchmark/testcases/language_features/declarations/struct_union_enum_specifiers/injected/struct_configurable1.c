struct {
  int a;
#ifdef ENABLE_A
  int x;
#endif
#ifdef ENABLE_B
  int y;
#endif
} a;

int main() {
  #if defined ENABLE_A && defined ENABLE_B
  int flag = sizeof(a) == 12;
  #elif defined ENABLE_A || defined ENABLE_B
  int flag = sizeof(a) == 8;
  #else
  int flag = sizeof(a) == 4;
  #endif
  return flag;
}
