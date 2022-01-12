int
#ifdef ENABLE_A
  *
#else
  **
#endif
    c;

int main() {
  #ifdef ENABLE_A
  int flag = sizeof(*c) == 4;
  #else
  int flag = sizeof(*c) == 8;
  #endif
  return flag;
}
