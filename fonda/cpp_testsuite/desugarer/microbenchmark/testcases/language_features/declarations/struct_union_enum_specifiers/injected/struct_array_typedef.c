typedef struct {
  unsigned long int a[16];
} Y;

struct X {
  Y b;
};

#ifdef ENABLE_A
typedef struct X testStruct[1];
testStruct x;
#else
int x;
#endif

int main() {
  #ifdef ENABLE_A
  int flag = sizeof(x) == 128;
  #else
  int flag = sizeof(x) == 4;
  #endif
  return flag;
}
