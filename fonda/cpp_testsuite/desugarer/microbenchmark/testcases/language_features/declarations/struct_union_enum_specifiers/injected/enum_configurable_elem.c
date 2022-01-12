#ifdef ENABLE_A
#define START 1
#else
#define START 0
#endif
enum E {B = START, C, D, E};

int main() {
  enum E a = B;
  #ifdef ENABLE_A
  int flag = a == 1;
  #else
  int flag = a == 0;
  #endif
  return flag;
}
