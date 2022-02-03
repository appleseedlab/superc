#ifdef ENABLE_A
typedef int x;
#else
typedef short x;
#endif

int main() {
  x id[2] = {1, 2};
  #ifdef ENABLE_A
  return sizeof(id);
  #else
  return sizeof(id);
  #endif
}
